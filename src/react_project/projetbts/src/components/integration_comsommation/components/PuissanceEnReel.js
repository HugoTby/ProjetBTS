import React, { useState, useEffect } from 'react';
import './PuissanceEnReel.css'; 

function PuissanceEnReel() {
  const [powerData, setPowerData] = useState([]);
  const [unit, setUnit] = useState('W');
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  const fetchPowerData = async () => {
    try {
      const response = await fetch('http://192.168.65.12:8050/selectPui');
      if (!response.ok) {
        throw new Error('Erreur lors de la récupération des données');
      }
      const data = await response.json();
      setPowerData(data);
      setLoading(false);
    } catch (err) {
      setError(err.message);
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchPowerData();
    const interval = setInterval(fetchPowerData, 5000); // Mettre à jour toutes les 5 secondes
    return () => clearInterval(interval);
  }, []);

  const changeUnit = (newUnit) => {
    setUnit(newUnit);
  };

  const convertPower = (power) => {
    switch (unit) {
      case 'kW':
        return (power / 1000).toFixed(2) + ' kW';
      case 'mW':
        return (power * 1000).toFixed(2) + ' mW';
      default:
        return power.toFixed(2) + ' W';
    }
  };

  if (loading) {
    return <div>Chargement des données...</div>;
  }

  if (error) {
    return <div>Erreur : {error}</div>;
  }

  return (
    <div className="puissance-container">
      <h2>Afficher les valeurs de puissance des panneaux photovoltaïques</h2>
      <ul>
        {powerData.map((panneau) => (
          <li key={panneau.id_panneau}>
            Capteur ID: {panneau.id_capteur} - Puissance: {convertPower(panneau.puissance)}
          </li>
        ))}
      </ul>
      <p>Unité :
        <button onClick={() => changeUnit('W')}>W</button>
        <button onClick={() => changeUnit('kW')}>kW</button>
        <button onClick={() => changeUnit('mW')}>mW</button>
      </p>
    </div>
  );
}

export default PuissanceEnReel;
