import React, { useState, useEffect, useRef } from 'react';
import Graphique from 'chart.js/auto';
import axios from 'axios';

const GraphiqueLuminosite = () => {
  const [donneesLuminosite, setDonneesLuminosite] = useState([]);
  const [datesDisponibles, setDatesDisponibles] = useState([]);
  const [dateSelectionnee, setDateSelectionnee] = useState('');
  const refGraphique = useRef(null);

  const obtenirDonneesLuminosite = async () => {
    try {
      const response = await axios.get('http://192.168.65.12:8080/selectLumi');
      const donnees = response.data;

      // Extraire toutes les dates disponibles
      const dates = Array.from(new Set(donnees.map(entry => new Date(entry.date).toDateString())));
      setDatesDisponibles(dates);

      // Si une date est sélectionnée, filtrer les données par cette date
      if (dateSelectionnee) {
        const donneesFiltrees = donnees.filter(entry => {
          const dateEntry = new Date(entry.date).toDateString();
          return dateEntry === dateSelectionnee;
        }).map(entry => entry.luminosité);
        setDonneesLuminosite(donneesFiltrees);
      } else {
        setDonneesLuminosite(donnees.map(entry => entry.luminosité));
      }
    } catch (error) {
      console.error('Erreur lors de la récupération des données de luminosité : ', error);
    }
  };

  useEffect(() => {
    obtenirDonneesLuminosite();
    const intervalId = setInterval(obtenirDonneesLuminosite, 5000);

    return () => clearInterval(intervalId);
  }, [dateSelectionnee]);

  useEffect(() => {
    if (donneesLuminosite.length > 0) {
      if (!refGraphique.current) {
        const ctx = document.getElementById('graphiqueLuminosite');
        refGraphique.current = new Graphique(ctx, {
          type: 'line',
          data: {
            labels: Array.from({ length: donneesLuminosite.length }, (_, i) => i + 1),
            datasets: [{
              label: 'Luminosité',
              data: donneesLuminosite,
              borderColor: 'rgb(75, 192, 192)',
              tension: 0.1
            }]
          },
          options: {
            scales: {
              y: {
                beginAtZero: true,
                ticks: {
                  callback: function(value) {
                    return value + ' lux'; // Ajout de l'unité "lux" sur les ticks de l'axe y
                  }
                }
              }
            },
            plugins: {
              tooltip: {
                callbacks: {
                  label: function(tooltipItem) {
                    return tooltipItem.raw + ' lux'; // Ajout de l'unité "lux" dans les infobulles
                  }
                }
              }
            }
          }
        });
      } else {
        refGraphique.current.data.labels = Array.from({ length: donneesLuminosite.length }, (_, i) => i + 1);
        refGraphique.current.data.datasets[0].data = donneesLuminosite;
        refGraphique.current.update();
      }
    }
  }, [donneesLuminosite]);

  return (
    <div>
      <h2>Graphique de luminosité en temps réel</h2>
      <select value={dateSelectionnee} onChange={(e) => setDateSelectionnee(e.target.value)}>
        <option value="">Sélectionner une date</option>
        {datesDisponibles.map(date => (
          <option key={date} value={date}>{date}</option>
        ))}
      </select>
      <canvas id="graphiqueLuminosite" width="400" height="200"></canvas>
    </div>
  );
};

export default GraphiqueLuminosite;
