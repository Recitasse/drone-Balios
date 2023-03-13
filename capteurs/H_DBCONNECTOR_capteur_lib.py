# =============================================================
# -------- Création de la base de donnée du sonar --------------
def sonar(cursor, db):
   # pour éviter d'accumuler des données lors des initialisations
   cursor.execute("DROP TABLE IF EXISTS capteur_sonar")
   sonar = """CREATE TABLE IF NOT EXISTS capteur_sonar (
           profondeur FLOAT NOT NULL DEFAULT 0,
           TEMPS_RECEPTION TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6))"""
   # Création de la table 
   cursor.execute(sonar)
   db.commit()
# ---------- Insertions des données du sonar ---------------
def integration_sonar(DATA, cursor, db):
   query = '''INSERT INTO capteur_sonar (profondeur) VALUES (%s)'''
   res = cursor.execute(query, (DATA,))
   db.commit()
# --------- Lecture des données du sonar -----------
def lecture_capteur_sonar(cursor):
   query = "SELECT * FROM capteur_sonar ORDER BY TEMPS_RECEPTION DESC LIMIT 1"
   cursor.execute(query)
   result = cursor.fetchone()
   print(result)
# ---------- Fonction explode ----------------------
def explode(separateur, phrase):
   return string.split(separateur)
# =============================================================
   
   
   
   
