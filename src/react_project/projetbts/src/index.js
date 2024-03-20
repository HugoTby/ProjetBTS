import React from 'react';
import ReactDOM from 'react-dom/client';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import './index.css';
import AccueilComponent from './components/accueil';
import APropos from './components/apropos';
import Informations from './components/informations';
import Navigation from './components/Navigation'; // Importez le composant Navigation
import reportWebVitals from './reportWebVitals';
import Error from './components/errorpage';
import EspaceUser from './components/Espaceutilisateur';

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  <React.StrictMode>
    <Router>
      <Navigation /> {/* Ajoutez le composant Navigation à l'arborescence des composants */}
      <Routes>
        <Route path="/" element={<AccueilComponent />} />
        <Route path="/about" element={<APropos />} />
        <Route path="/current-news" element={<Informations />} />
        <Route path="/account" element={<EspaceUser />} />
        <Route path="*" element={<Error />} />
      </Routes>

    </Router>
  </React.StrictMode>
);

reportWebVitals();
