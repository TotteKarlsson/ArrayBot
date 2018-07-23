import mysql.connector
import csv

cnx = mysql.connector.connect(user='atdb_client', password='atdb123',
                              host='127.0.0.1', database='atdb')

cursor = cnx.cursor()

#18 records
specimen = ("INSERT INTO specimen "
               "(specimen_id, species, additional_identifier, age, death_date, preprocess_treatment, fixative,  fixation_method,  brain_region_dissection,  postfix_protocol,  date_received,  date_embedded,  cryoprotection_protocol,  freezing_protocol,  substitution_protocol,  infiltration_protocol,  embedding_protocol ) "
               "VALUES ( %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s )")

specData = []

#Read specimen data from csv file
with open('p://atDB/docs/tsv.csv', 'rb') as csvfile:
    rows = csv.reader(csvfile, delimiter=',', quotechar='|')

    for row in rows:
        specData = []
        for col in range(0,17):
            specData.append(row[col] )
         #   print specData
        print specData

        try:
            cursor.execute(specimen, specData)
            newID = cursor.lastrowid
            print `newID`
        except mysql.connector.Error as err:
            print("Something went wrong: {}".format(err))

cnx.commit()
cursor.close()

cnx.close()
