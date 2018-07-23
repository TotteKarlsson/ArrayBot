import cv2
import os
import sys
import dsl
import time
import logging

# Plugin Name and Plugin Category
def createPluginMetaData():
    pInfo = dsl.PluginMetaData("getImageROI", "Basic")
    pInfo.setAuthor("Totte Karlsson")
    pInfo.setDescription("Create a cropped image.")
    pInfo.setCopyright("Allen Institute for Brain Science, 2018")
    pInfo.setHint("Crop Image")
    pInfo.setCategory("Misc Plugins")
    return pInfo

# Setup the plugins properties, used later on when execution occurs
def  createPluginProperties():
        props       = dsl.Properties("ROI Plugin Properties")
        logFileName = dsl.stringProperty("Log.txt", "ApplicationLogFile")
        sourceFName = dsl.stringProperty("NoName", "SourceImageFileName")
        x           = dsl.intProperty(0, "X")
        y           = dsl.intProperty(0, "Y")
        height      = dsl.intProperty(0, "Height")
        width       = dsl.intProperty(0, "Width")
        outFName    = dsl.stringProperty("NoName", "CroppedImageFileName")

        props.add(logFileName)
        props.add(x)
        props.add(y)
        props.add(height)
        props.add(width)
        props.add(sourceFName)
        props.add(outFName)
        return props

def cropImage(imageF, x, y, h, w):
    img = cv2.imread(imageF, cv2.IMREAD_COLOR)
    cropped_img = img[y:y+h, x:x+w]
    imagePath = os.path.dirname(os.path.abspath(imageF))
    imageFNameNoExtension = os.path.splitext(os.path.basename(imageF))[0]
    outFName = os.path.join(imagePath, imageFNameNoExtension + "-cropped.jpg")
    cv2.imwrite(outFName, cropped_img)
    return outFName

## The execute function is called from C/C++ with a PythonPlugin object
## as argument. The python code below assume that the plugins properties and metadata has been setup from
## within c/c++, using the above functions
def execute(thePlugin):
    logFileName = thePlugin.getPropertyValueString("ApplicationLogFile")
    logging.basicConfig(filename=logFileName, level=logging.DEBUG)
    logging.debug('Executing the Python Plugin')
    inFName = thePlugin.getPropertyValueString("SourceImageFileName")
    x       = thePlugin.getPropertyValueInt("X")
    y       = thePlugin.getPropertyValueInt("Y")
    height  = thePlugin.getPropertyValueInt("Height")
    width   = thePlugin.getPropertyValueInt("Width")
    outFName = cropImage(inFName, x, y, height, width)
    thePlugin.setPropertyValue("CroppedImageFileName", outFName)
    return True

#Main function is used for testing..
def main():
    try:
        pm = dsl.PythonPluginManager()
        plugin = pm.createBarePlugin("Test")

        md = createPluginMetaData()
        plugin.assignMetaData(md)
        props = createPluginProperties()

        pluginProps = plugin.getProperties()
        for i in range(props.count()):
            p = props.getProperty(i)
            print("Have property: " + p.getLabel())
            pluginProps.add(p)

        srcFName = "p:/temp/Image1.jpg"
        plugin.setPropertyValue("SourceImageFileName", srcFName)

        p = plugin.getProperty("SourceImageFileName")
        print( p.getValueAsString())

        for i in range(1):
            x, y, h, w = 500+i, 300 + i, 400, 200
            plugin.setPropertyValue("X", x)
            plugin.setPropertyValue("Y", y)
            plugin.setPropertyValue("Height", h)
            plugin.setPropertyValue("Width", h)
            res = execute(plugin)

    except: # catch exceptions
        e = sys.exc_info()[0]
        print ("There was a problem: " + str(e))

    finally:
        #Its important to call this, in order to clean up memory properly
        pm.unloadAll()


if __name__ == '__main__':
    main()
