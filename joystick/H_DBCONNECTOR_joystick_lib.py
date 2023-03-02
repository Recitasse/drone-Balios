# Les fonctions utilisées
# -------- Création de la base de donnée du joystick --------------

def Joystick(cursor, db):
   # pour éviter d'accumuler des données lors des initialisations
   cursor.execute("DROP TABLE IF EXISTS commande_manette")
   manette = """CREATE TABLE IF NOT EXISTS commande_manette (
           psi FLOAT(3,1) NOT NULL DEFAULT 0,
           V_y TINYINT(4) NOT NULL DEFAULT 0,
           V_x TINYINT(4) NOT NULL DEFAULT 0,
           MODE_TURBO TINYINT(2) NOT NULL DEFAULT 0,
           INVERSION_COMMANDE TINYINT(2) NOT NULL DEFAULT 1,
           MODE_AUTO TINYINT(1) NOT NULL DEFAULT 0,
           TEMPS_RECEPTION TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6))"""
   # Création de la table 
   cursor.execute(manette)
   db.commit()

# ---------- Insertions des données du joystick ---------------
def integration_commande(DATA, cursor, db):
   query = '''INSERT INTO commande_manette (psi, V_y, V_x, MODE_TURBO, INVERSION_COMMANDE, MODE_AUTO) VALUES (%s, %s, %s, %s, %s, %s)'''
   valeurs = [DATA['POSITION']['PSI'], DATA['POSITION']['Y'], DATA['POSITION']['X'], DATA['REGLAGE']['MODE'], DATA['REGLAGE']['INVERSE'], DATA['REGLAGE']['AUTO']]
   res = cursor.execute(query, valeurs)
   db.commit()

# --------- Lecture des données du joystick -----------
def lecture_manette_commande(cursor):
   query = "SELECT * FROM commande_manette ORDER BY TEMPS_RECEPTION ASC LIMIT 1"
   cursor.execute(query)
   result = cursor.fetchone()
   
   
   
   
   
