import mysql.connector

# Connexion à la base de donnée
def connexion_db(nom):
   db = mysql.connector.connect(host="localhost", user="balios", password="droneBalios1", database=nom)
   # Création du curseur
   cursor = db.cursor()
   return cursor, db

  
