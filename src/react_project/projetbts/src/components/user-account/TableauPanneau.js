import React, { useState, useEffect } from 'react';
import './TableauPanneau.css';

const TableauPanneau = () => {
  const [energieData, setEnergieData] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [startDate, setStartDate] = useState('');
  const [endDate, setEndDate] = useState('');

  const fetchEnergieData = async () => {
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
      const data = await response.json();
      setEnergieData(data);
      setLoading(false);
    } catch (err) {
      setError(err.message);
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchEnergieData();
    const intervalle = setInterval(fetchEnergieData, 5000);
    return () => clearInterval(intervalle);
  }, []);

  const handleStartDateChange = (e) => {
    setStartDate(e.target.value);
  };

  const handleEndDateChange = (e) => {
    setEndDate(e.target.value);
  };

  const filteredData = energieData.filter(item => {
    const itemDate = new Date(item.date);
    const start = startDate ? new Date(startDate) : new Date('1970-01-01');
    const end = endDate ? new Date(endDate) : new Date();
    return itemDate >= start && itemDate <= end;
  });

  if (loading) {
    return <div>Chargement des données...</div>;
  }

  if (error) {
    return <div>Erreur : {error}</div>;
  }

  return (
    <div className="TableauPanneau-container"style={{
      height: '500px',
      overflowY: 'auto',
      margin: '5%',
      borderRadius: '15px',
    }}>
      <h2>Suivi de production d'énergie verte</h2>
      <div className="TableauPanneau-filters">
        <label>
          Date et heure de début : &nbsp;
          <input type="datetime-local" value={startDate} onChange={handleStartDateChange} />
        </label><br></br>
        <label>
          Date et heure de fin : &nbsp;
          <input type="datetime-local" value={endDate} onChange={handleEndDateChange} />
        </label>
      </div>
      <table className="TableauPanneau-table">
        <thead>
          <tr>
            <th>Date</th>
            <th>Heure</th>
            <th>Production d'énergie (Wh)</th>
          </tr>
        </thead>
        <tbody>
        {filteredData.reverse().map((item, index) => ( // Utiliser reverse() ici
          <tr key={index}>
            <td>{new Date(item.date).toLocaleDateString()}</td>
            <td>{new Date(item.date).toLocaleTimeString()}</td>
            <td>{item.production_energie.toFixed(2)}</td>
          </tr>
        ))}
      </tbody>
      </table>
    </div>
  );
};

export default TableauPanneau;
