import dsl

def getPluginMetaData():
    pInfo = dsl.PluginMetaData("DemoPlugin_1", "tests")
    pInfo.setAuthor("Totte Karlsson")
    pInfo.setDescription("Python Demo plugin")
    pInfo.setCategory("Python Demo Plugin")
    pInfo.add("Custom field", "Custom field value")
    return pInfo

def getPluginProperties():
    props = dsl.foundation.P

def multiply(a,b):
    print("Compute", a, "times", b)
    return a * b

def execute(a, b):
    print ("We are executing ..")
    return multiply(a,b)
