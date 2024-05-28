// Déclaration des broches
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
String input;
int currentLed = -1; // Index de la LED actuellement allumée
unsigned long ledOnTime = 0; // Heure à laquelle la LED a été allumée

void setup() {
  // Configuration des broches en sortie
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Extinction des LED au démarrage
  }
  // Initialisation du moniteur série
  Serial.begin(9600);
  
  Serial.print("Ready to receive data ...\n\n");
}

void loop() {

  // Vérification si des données sont disponibles dans le moniteur série
  if (Serial.available() > 0) {
    input = Serial.readString();
    // Comparaison de l'entrée avec "LEDONX"
    if (input.startsWith("LEDON_PLAN")) {
      int pinNumber = input.substring(10).toInt(); // Récupération du numéro de broche
      // Vérification que le numéro de broche est valide
      if (pinNumber >= 2 && pinNumber <= 9) {
        int ledIndex = pinNumber - 2; // Calcul de l'index dans le tableau ledPins
        if (currentLed != -1) { // Si une LED est déjà allumée
          digitalWrite(ledPins[currentLed], LOW); // Extinction de la LED actuelle
          Serial.println("Previous light off");
        }
        digitalWrite(ledPins[ledIndex], HIGH); // Allumage de la nouvelle LED
        Serial.println("Actual light on : " + String(pinNumber) + ", for box " + String(pinNumber-1));
        currentLed = ledIndex; // Mise à jour de l'index de la LED actuelle
        ledOnTime = millis(); // Mise à jour de l'heure à laquelle la LED a été allumée
      }
    }
    // Comparaison de l'entrée avec "shutdown"
    else if (input == "SHUTDOWN_PLAN") {
      // Extinction des LED
      for (int i = 0; i < 8; i++) {
        digitalWrite(ledPins[i], LOW);
      }
      Serial.println("Shutdown processes applied");
      // Arrêt de la boucle principale
      while (true) {}
    }
  }

  // Vérification si la LED actuelle doit être éteinte
  if (currentLed != -1 && millis() - ledOnTime >= 30000) {
    digitalWrite(ledPins[currentLed], LOW); // Extinction de la LED actuelle
    currentLed = -1; // Réinitialisation de l'index de la LED actuelle
    Serial.println("Last light off cause time's up");
  }

  // Attente de 100 millisecondes
  delay(100);
}


