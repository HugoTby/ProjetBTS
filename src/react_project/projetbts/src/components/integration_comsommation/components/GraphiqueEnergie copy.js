import React, { useState, useEffect, useRef } from 'react';
import Chart from 'chart.js/auto';

const GraphiqueEnergie = () => {
  const [donneesEnergie, setDonneesEnergie] = useState([]);
  const [datesDisponibles, setDatesDisponibles] = useState([]);
  const [dateSelectionnee, setDateSelectionnee] = useState('');
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const chartRef = useRef(null);

  const fetchDonneesEnergie = async () => {
    try {
      const response = await fetch('http://192.168.65.12:8050/api/selectPui', {
        headers: {
          'Accept': 'application/json',
          'x-api-key': 'root'
        }
      });

      if (!response.ok) {
        throw new Error('Erreur lors de la récupération des données');
      }

      const donnees = await response.json();

      // Extraire toutes les dates disponibles
      const dates = Array.from(new Set(donnees.map(entry => new Date(entry.date).toDateString())));
      setDatesDisponibles(dates);

      // Si une date est sélectionnée, filtrer les données par cette date
      if (dateSelectionnee) {
        const donneesFiltrees = donnees.filter(entry => {
          const dateEntry = new Date(entry.date).toDateString();
          return dateEntry === dateSelectionnee;
        }).map(entry => entry.production_energie);
        setDonneesEnergie(donneesFiltrees);
      } else {
        setDonneesEnergie(donnees.map(entry => entry.production_energie));
      }
    } catch (error) {
      setError('Erreur lors de la récupération des données : ' + error.message);
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchDonneesEnergie();
    const intervalId = setInterval(fetchDonneesEnergie, 5000);

    return () => clearInterval(intervalId);
  }, [dateSelectionnee]);

  useEffect(() => {
    if (donneesEnergie.length > 0) {
      if (!chartRef.current) {
        const ctx = document.getElementById('graphiqueEnergie');
        chartRef.current = new Chart(ctx, {
          type: 'line',
          data: {
            labels: Array.from({ length: donneesEnergie.length }, (_, i) => i + 1),
            datasets: [{
              label: 'Production d’énergie',
              data: donneesEnergie,
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
                    return value + ' kWh'; // Ajout de l'unité "kWh" sur les ticks de l'axe y
                  }
                }
              }
            },
            plugins: {
              tooltip: {
                callbacks: {
                  label: function(tooltipItem) {
                    return tooltipItem.raw + ' kWh'; // Ajout de l'unité "kWh" dans les infobulles
                  }
                }
              }
            }
          }
        });
      } else {
        chartRef.current.data.labels = Array.from({ length: donneesEnergie.length }, (_, i) => i + 1);
        chartRef.current.data.datasets[0].data = donneesEnergie;
        chartRef.current.update();
      }
    }
  }, [donneesEnergie]);

  if (loading) {
    return <div>Loading...</div>;
  }

  if (error) {
    return <div>Error: {error}</div>;
  }

  return (
    <div>
      <h2>Graphique de production d’énergie en temps réel</h2>
      <select value={dateSelectionnee} onChange={(e) => setDateSelectionnee(e.target.value)}>
        <option value="">Sélectionner une date</option>
        {datesDisponibles.map(date => (
          <option key={date} value={date}>{date}</option>
        ))}
      </select>
      <canvas id="graphiqueEnergie" width="400" height="200"></canvas>
    </div>
  );
};

export default GraphiqueEnergie;
