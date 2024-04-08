const express = require('express');
const mysql = require('mysql');
const cors = require('cors');
const bodyParser = require('body-parser');
const app = express();
const port = 5001;

app.use(cors());
app.use(bodyParser.json());
// Configuration de la connexion à la base de données
const connection = mysql.createConnection({
    host: '192.168.65.105',
    user: 'debian',
    password: 'root',
    database: 'sandbox_projet_bts'
});

// Connecter à la base de données
connection.connect((err) => {
    if (err) {
        console.error('Erreur lors de la connexion à la base de données :', err);
        return;
    }
    console.log('Connecté à la base de données MySQL');
});

// Middleware pour analyser les requêtes JSON
// Middleware pour gérer les erreurs JSON
app.use((error, req, res, next) => {
    if (error instanceof SyntaxError) {
        console.error('Erreur de syntaxe JSON :', error);
        console.log('Corps de la requête :', req.body);
        res.status(400).json({ error: 'Erreur de syntaxe JSON dans la requête' });
    } else {
        next();
    }
});



// Route pour récupérer tous les éléments de la base de données
app.get('/utilisateurs', (req, res) => {
    connection.query('SELECT utilisateur.*, occupation.*, box.*, occupation.heure_depot_occupation AS heure_depot, occupation.heure_retrait_occupation AS heure_retrait FROM utilisateur JOIN occupation ON utilisateur.id_utilisateur = occupation.id_utilisateur_occupation JOIN box ON occupation.id_box_occupation = box.id_box', (error, results) => {
        if (error) {
            console.error('Erreur lors de la récupération des éléments :', error);
            res.status(500).json({ error: 'Erreur lors de la récupération des éléments' });
            return;
        }
        res.json(results);
    });
});


// Route pour récupérer les éléments de la base de données avec le badge
app.get('/utilisateurs/badge_utilisateur', (req, res) => {
    console.log( req.body);
    //const { badge_utilisateur } = req.body;
    const badge_utilisateur = req.query.badge_utilisateur;
    console.log(badge_utilisateur);
    connection.query('SELECT * FROM `utilisateur` WHERE utilisateur.badge_utilisateur = ?', [badge_utilisateur], (error, results) => {
        if (error) {
            console.error('Erreur lors de la récupération des éléments :', error);
            res.status(500).json({ error: 'Erreur lors de la récupération des éléments' });
            return;
        }
        res.json(results);
    });
});

// Route pour récupérer le quota utilisateur et dernier heure depot utilisation avec le badge
app.get('/utilisateurs/badge_utilisateur/quota-depot', (req, res) => {
    console.log( req.body);
    //const { badge_utilisateur } = req.body;
    const badge_utilisateur = req.query.badge_utilisateur;
    console.log(badge_utilisateur);
    connection.query('SELECT u.quota_utilisateur, o.heure_depot_occupation FROM utilisateur u JOIN occupation o ON u.id_utilisateur = o.id_utilisateur_occupation WHERE u.badge_utilisateur = ? ORDER BY o.heure_depot_occupation DESC LIMIT 1;', [badge_utilisateur], (error, results) => {
        if (error) {
            console.error('Erreur lors de la récupération des éléments :', error);
            res.status(500).json({ error: 'Erreur lors de la récupération des éléments' });
            return;
        }
        res.json(results);
    });
});


// Route pour insérer un utilisateur dans la base de données
app.use(express.json());

app.post('/utilisateurs', (req, res) => {
    console.log(req.body);
    const { nom_utilisateur, prenom_utilisateur, classe_utilisateur, badge_utilisateur, password_utilisateur, telephone_utilisateur, mail_utilisateur, quota_utilisateur } = req.body;
    connection.query('INSERT INTO utilisateur (nom_utilisateur, prenom_utilisateur, classe_utilisateur, badge_utilisateur, password_utilisateur, telephone_utilisateur, mail_utilisateur, quota_utilisateur) VALUES (?, ?, ?, ?, ?, ?, ?, ?)', [nom_utilisateur, prenom_utilisateur, classe_utilisateur, badge_utilisateur, password_utilisateur, telephone_utilisateur, mail_utilisateur, quota_utilisateur], (error, results) => {
        if (error) {
            console.error('Erreur lors de l\'insertion de l\'utilisateur :', error);
            res.status(500).json({ error: 'Erreur lors de l\'insertion de l\'utilisateur' });
            return;
        }
        console.log("requete insertion ok");
        res.status(201).json({ message: 'Utilisateur inséré avec succès', id_utilisateur_inséré: results.insertId });
    });
});


// Route pour supprimer un utilisateur de la base de données en utilisant le nom et le prénom
app.delete('/utilisateurs', (req, res) => {
    const { id_utilisateur } = req.body;
    console.log( req.body);
    connection.query('DELETE FROM utilisateur WHERE id_utilisateur = ?', [id_utilisateur], (error, results) => {
        if (error) {
            console.error('Erreur lors de la suppression de l\'utilisateur :', error);
            res.status(500).json({ error: 'Erreur lors de la suppression de l\'utilisateur' });
            return;
        }
        if (results.affectedRows === 0) {
            res.status(404).json({ message: 'Utilisateur non trouvé' });
            return;
        }
        console.log("requete delete ok");
        res.json({ message: 'Utilisateur supprimé avec succès' });
    });
});

// Route pour mettre à jour toutes les informations d'un utilisateur en fonction du nom et du prénom
app.put('/utilisateurs', (req, res) => {
    const { nom_utilisateur, prenom_utilisateur, ...otherInfo } = req.body;

    // Construire la chaîne SQL pour mettre à jour les informations autres que le nom et le prénom
    let updateQuery = '';
    const updateParams = [];

    for (const key in otherInfo) {
        updateQuery += `${key} = ?, `;
        updateParams.push(req.body[key]);
    }
    updateQuery = updateQuery.slice(0, -2); // Supprimer la virgule finale

    // Mettre à jour les informations de l'utilisateur
    const query = `UPDATE utilisateur SET ${updateQuery} WHERE nom_utilisateur = ? AND prenom_utilisateur = ?`;

    connection.query(query, [...updateParams, nom_utilisateur, prenom_utilisateur], (error, results) => {
        if (error) {
            console.error('Erreur lors de la mise à jour des informations de l\'utilisateur :', error);
            res.status(500).json({ error: 'Erreur lors de la mise à jour des informations de l\'utilisateur' });
            return;
        }
        if (results.affectedRows === 0) {
            res.status(404).json({ message: 'Utilisateur non trouvé' });
            return;
        }
        console.log("requete update ok");
        res.json({ message: 'Informations de l\'utilisateur mises à jour avec succès' });
    });
});




/*****************************************************************************************************************************/
/*                                                                                                                           */
/*****************************************************************************************************************************/
// Route pour la connexion
// Route pour la connexion
app.post('/login', (req, res) => {
    const { username, password } = req.body;

    console.log('Requête de connexion reçue');
    console.log('Nom d\'utilisateur :', username);
    console.log('Mot de passe :', password);

    // Vérifier les informations d'identification de l'utilisateur dans la base de données
    connection.query(
      'SELECT * FROM utilisateur WHERE CONCAT(prenom_utilisateur, ".", nom_utilisateur) = ? AND password_utilisateur = ?',
      [username, password],
      (error, results) => {
        if (error) {
          console.error('Error during login:', error);
          res.status(500).json({ success: false, message: 'Erreur lors de la connexion' });
          return;
        }

        console.log('Résultats de la requête :', results);

        if (results.length === 0) {
          res.status(401).json({ success: false, message: 'Nom d\'utilisateur ou mot de passe incorrect' });
          return;
        }

        // Générer un jeton d'authentification ou renvoyer les informations utilisateur
        res.json({ success: true, message: 'Connexion réussie', user: results[0] });
      }
    );
});

/*****************************************************************************************************************************/









// Lancement du serveur
app.listen(port, () => {
    console.log(`Serveur Node.js démarré sur le port ${port}`);
});
