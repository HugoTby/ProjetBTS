const net = require('net');
const express = require('express');
const app = express();
const port = 3000;

// Adresse IP et port de l'Arduino
const arduinoIp = '192.168.64.100'; // Remplacez par l'adresse IP de votre Arduino
const arduinoPort = 3000; // Remplacez par le port de votre Arduino

// Fonction pour envoyer une commande à l'Arduino
function sendCommand(command) {
  const client = new net.Socket();
  client.connect(arduinoPort, arduinoIp, () => {
    client.write(command);
    client.end();
  });
}

// Points de terminaison de l'API
app.get('/shutdown', (req, res) => {
  sendCommand('SHUTDOWN_PLAN');
  res.send('Shutdown command sent');
});

app.get('/ledon/:pin', (req, res) => {
  const pin = req.params.pin;
  if (pin >= 2 && pin <= 9) {
    sendCommand(`LEDON_PLAN${pin}`);
    res.send(`LEDON command sent for pin ${pin}`);
  } else {
    res.send('Invalid pin number');
  }
});

// Démarrage du serveur
app.listen(port, () => {
  console.log(`API server listening at http://192.168.65.105:${port}`);
});
