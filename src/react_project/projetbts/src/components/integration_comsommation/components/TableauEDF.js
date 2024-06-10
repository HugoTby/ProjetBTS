import React, { useState, useEffect } from 'react';
import './TableauEDF.css';

const TableauEDF = () => {
  const [energieData, setEnergieData] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [startDate, setStartDate] = useState('');
  const [endDate, setEndDate] = useState('');

  const fetchEnergieData = async () => {
    try {
      const response = await fetch('http://192.168.65.12:8050/selectPui'); // Assurez-vous que l'endpoint est correct
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
    <div className="TableauEDF-container">
      <h2>Suivi de consommation d'énergie EDF</h2>
      <div className="TableauEDF-filters">
        <label>
          Date et heure de début:
          <input type="datetime-local" value={startDate} onChange={handleStartDateChange} />
        </label>
        <label>
          Date et heure de fin:
          <input type="datetime-local" value={endDate} onChange={handleEndDateChange} />
        </label>
      </div>
      <table className="TableauEDF-table">
        <thead>
          <tr>
            <th>Date</th>
            <th>Heure</th>
            <th>Suivi EDF</th>
          </tr>
        </thead>
        <tbody>
          {filteredData.map((item, index) => (
            <tr key={index}>
              <td>{new Date(item.date).toLocaleDateString()}</td>
              <td>{new Date(item.date).toLocaleTimeString()}</td>
              <td>{item.SuiviEdf}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default TableauEDF;
