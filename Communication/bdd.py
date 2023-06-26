import mysql.connector

class BDD:
    def __init__(self, nom:str) -> None:
        self.db = mysql.connector.connect(host="localhost", user="balios", password="droneBalios1", database=nom)
        self.cursor = self.db.cursor()

    def creation_tables(self):
        # Création de la table sonar
        self.cursor.execute("DROP TABLE IF EXISTS capteur_sonar")
        sonar = """CREATE TABLE IF NOT EXISTS capteur_sonar (
                profondeur FLOAT NOT NULL DEFAULT -1000,
                TEMPS_RECEPTION TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6))"""
        self.cursor.execute(sonar)
        self.db.commit()

        # Création de la table latitude
        self.cursor.execute("DROP TABLE IF EXISTS capteur_gps_lat")
        gps_latitude = """CREATE TABLE IF NOT EXISTS capteur_gps_lat (
                latitude FLOAT NOT NULL DEFAULT -1000,
                TEMPS_RECEPTION TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6))"""
        self.cursor.execute(gps_latitude)
        self.db.commit()

        # Création de la table longitude
        self.cursor.execute("DROP TABLE IF EXISTS capteur_gps_long")
        gps_longitude = """CREATE TABLE IF NOT EXISTS capteur_gps_long (
                longitude FLOAT NOT NULL DEFAULT -1000,
                TEMPS_RECEPTION TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6))"""
        self.cursor.execute(gps_longitude)
        self.db.commit()

    def integration_sonar(self, prof:float):
        query = '''INSERT INTO capteur_sonar (profondeur) VALUES (%s)'''
        self.cursor.execute(query, (prof,))
        self.db.commit()

    def integration_gps_long(self, long:float):
        query = '''INSERT INTO capteur_gps_long (longitude) VALUES (%s)'''
        self.cursor.execute(query, (long,))
        self.db.commit()

    def integration_gps_lat(self, lat:float):
        query = '''INSERT INTO capteur_gps_lat (latitude) VALUES (%s)'''
        self.cursor.execute(query, (lat,))
        self.db.commit()
    
   
