import dsl
import time
import sys

# Plugin Name and Plugin Category
def getPluginMetaData():
    pInfo = dsl.PluginMetaData("showTempHumidityPlugin", "Basic")
    pInfo.setAuthor("Totte Karlsson")
    pInfo.setDescription("Show Temperature and Humidity as a function of time")
    pInfo.setCopyright("Allen Institute for Brain Science, 2018")
    pInfo.setHint("Show Temperature History")
    pInfo.setCategory("Misc Plugins")
    return pInfo

# Setup the plugins properties, used later on when execution occurs
def getPluginProperties():
        props = dsl.Properties("TempAndHumidity")
        i1    = dsl.intProperty(30, "Days")
        i1.thisown = 0
        props.add(i1)
        return props

## The execute function is called from C/C++ with a PythonPlugin object
## as argument. The python code assume that the plugins properties and metadata has been setup from
## within c/c++, using the above functions
def execute(thePlugin):
    daysProperty = thePlugin.getProperty("Days")
    days  = daysProperty.getValueAsString()
    print ("Get environmental data for the last consecutive " + days + " days.")
    return int(days) + 3

def executeInt(anInt):
    days  = str(anInt)
    print ("Get environmental data for the last consecutive " + days + " days.")
    return int(days) + 3

def executeInt(anInt):

    days  = str(anInt)
    print ("Get environmental data for the last consecutive " + days + " days.")
    return int(days) + 3

##The main function allow debugging of the plugin from within python
def main():
    try:
        pm = dsl.PythonPluginManager("Test")
        pp = pm.createBarePlugin("Test")
        md = getPluginMetaData()
        pp.assignMetaData(md)
        props = getPluginProperties()

        for i in range(props.count()):
            p = props.getProperty(i)
            print("Adding property: " + p.getLabel())
            pprops = pp.getProperties()
            pprops.add(p)

        for i in range(1000):
            print ("Hello")

            bp = props.getProperty("Days")
            bp.assignValueFromString(str(i))

            res = execute(pp)
            print (res)

        pm.unloadAll()
        print ("Done..")

    except: # catch exceptions
        e = sys.exc_info()[0]
        print ("There was a problem: " + str(e))

if __name__ == '__main__':
    main()

