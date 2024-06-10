import React, { useState, useEffect } from 'react';
import './IntensiteEnReel.css'; 

function IntensiteEnReel() {
  const [intensityData, setIntensityData] = useState([]);
  const [unit, setUnit] = useState('A');
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  const fetchIntensityData = async () => {
    try {
      const response = await fetch('http://192.168.65.12:8050/selectPui'); // Assurez-vous que l'endpoint est correct
      if (!response.ok) {
        throw new Error('Erreur lors de la récupération des données');
      }
      const data = await response.json();
      setIntensityData(data);
      setLoading(false);
    } catch (err) {
      setError(err.message);
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchIntensityData();
    const interval = setInterval(fetchIntensityData, 5000); // Mettre à jour toutes les 5 secondes
    return () => clearInterval(interval);
  }, []);

  const changeUnit = (newUnit) => {
    setUnit(newUnit);
  };

  const convertIntensity = (intensity) => {
    switch (unit) {
      case 'mA':
        return (intensity * 1000).toFixed(2) + ' mA';
      case 'µA':
        return (intensity * 1000000).toFixed(2) + ' µA';
      default:
        return intensity.toFixed(2) + ' A';
    }
  };

  if (loading) {
    return <div>Chargement des données...</div>;
  }

  if (error) {
    return <div>Erreur : {error}</div>;
  }

  return (
    <div className="intensite-container">
      <h2>Afficher les valeurs de l'intensité des panneaux photovoltaïques</h2>
      <ul>
        {intensityData.map((panneau) => (
          <li key={panneau.id_panneau}>
            Capteur ID: {panneau.id_capteur} - Intensité: {convertIntensity(panneau.intensité)}
          </li>
        ))}
      </ul>
      <p>Unité :
        <button onClick={() => changeUnit('A')}>A</button>
        <button onClick={() => changeUnit('mA')}>mA</button>
        <button onClick={() => changeUnit('µA')}>µA</button>
      </p>
    </div>
  );
}

export default IntensiteEnReel;
