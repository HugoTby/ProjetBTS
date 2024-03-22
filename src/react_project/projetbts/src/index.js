import React from 'react';
import ReactDOM from 'react-dom/client';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import './index.css';
import AccueilComponent from './components/accueil';
import APropos from './components/apropos';
import Informations from './components/informations';
import reportWebVitals from './reportWebVitals';
import Error from './components/errorpage';
import EspaceUser from './components/Espaceutilisateur';
import ForgottenPassword from './components/resetpassword';
import UserMain from './components/user-account/main';
import Contact from './components/contact';
import Layout from './Layout';

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  <React.StrictMode>
    <Router>
      <Routes>
        <Route path="/" element={<Layout><AccueilComponent /></Layout>} />
        <Route path="/about" element={<Layout><APropos /></Layout>} />
        <Route path="/current-news" element={<Layout><Informations /></Layout>} />
        <Route path="/sign-in" element={<Layout><EspaceUser /></Layout>} />
        <Route path="/forgotten-password" element={<Layout><ForgottenPassword /></Layout>} />
        <Route path="/contact" element={<Layout><Contact /></Layout>} />
        <Route path="/user-profile" element={<UserMain />} />
        <Route path="*" element={<Error />} />
      </Routes>
    </Router>
  </React.StrictMode>
);

reportWebVitals();
