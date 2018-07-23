import atp

#Create a properties container
props = atp.Properties("Testing")

#Create some properties
p1 = atp.intProperty(34, "An intProperty")
p2 = atp.stringProperty("My String")

#Add some properties to the container
props.add(p1)
props.add(p2)
props.add(atp.stringProperty("Another String Property"))

#Retrieve a property
a = props.getProperty(0)

#Query the property
print ("The label for this property is: " + a.getLabel())
print ("There are " + str(props.count()) + " properties available in the properties container.")