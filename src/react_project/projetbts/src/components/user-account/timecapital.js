import React, { useState, useEffect } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import Cookies from 'js-cookie';
import axios from 'axios';
import './css/main.css';
import './js/script.js';

function UserTimeCapital() {
  const navigate = useNavigate();

  const [dropdownIsOpen, setDropdownIsOpen] = useState(false);
  const [userQuota, setUserQuota] = useState(null);

  const handleDropdownClick = (event) => {
    if (event.target.classList.contains('dropdown-toggler') || event.target.classList.contains('dropdown-toggler2')) {
      event.preventDefault(); // Empêche le comportement par défaut de l'élément <a> seulement si l'élément cible a la classe "dropdown-toggler" ou "dropdown-toggler2"
    }
    const target = document.querySelector(`#${event.target.dataset.dropdown}`);
    if (target) {
      setDropdownIsOpen(!dropdownIsOpen);
      target.classList.toggle('show');
    }
  };

  const checkCookie = () => {
    console.log('Vérification du cookie...');
    const user = Cookies.get('user');
    if (!user) {
      navigate('/sign-in');
    } else {
      const parsedUser = JSON.parse(user);
      const username = `${parsedUser.prenom_utilisateur}.${parsedUser.nom_utilisateur}`;
      console.log('user', username);
      fetchUserQuota(username);
    }
  };

  const fetchUserQuota = async (username) => {
    console.log('Récupération du quota pour :', username);
    try {
      const response = await axios.get(`http://192.168.65.105:5001/utilisateurs/quota/${username}`);
      if (response.data.success) {
        setUserQuota(response.data.quota);
      } else {
        console.error("Erreur lors de la récupération du quota : ", response.data.message);
      }
    } catch (error) {
      console.error("Erreur lors de la requête du quota : ", error);
    }
  };

  const handleOutsideClick = (event) => {
    if (dropdownIsOpen && !event.target.closest('.navbar2-dropdown')) {
      setDropdownIsOpen(false);
      document.querySelector('.dropdown.show').classList.remove('show');
    }
  };

  const handleLogout = (event) => {
    event.preventDefault();
    // Supprimez le cookie de connexion
    Cookies.remove('user');
  };

  useEffect(() => {
    checkCookie();

    const dropdownButtons = document.querySelectorAll('.dropdown-toggler');
    dropdownButtons.forEach((dropdownButton) => {
      dropdownButton.addEventListener('click', handleDropdownClick);
    });

    window.addEventListener('mouseup', handleOutsideClick);

    return () => {
      dropdownButtons.forEach((dropdownButton) => {
        dropdownButton.removeEventListener('click', handleDropdownClick);
      });
      window.removeEventListener('mouseup', handleOutsideClick);
    };
  }, []);

  return (
    <div>
      <nav className="navbar2">
        <div className="container3">
          <div className="navbar2-header">
            <button className="navbar2-toggler" data-toggle="open-navbar1">
              <span></span>
              <span></span>
              <span></span>
            </button>
            <a href="">
              <h4>La Providence <span>Amiens</span></h4>
            </a>
          </div>

          <div className="navbar2-menu" id="open-navbar1">
            <ul className="navbar2-nav">
              <li className="active"><a href=""><Link to="/user-profile">Accueil</Link></a></li>
              <li className="navbar2-dropdown">
                <a href="" className="dropdown-toggler" data-dropdown="my-dropdown-id">
                  Catégories <i className="fa fa-angle-down"></i>
                </a>
                <ul className="dropdown" id="my-dropdown-id">
                  <li><a href="/time-capital">Mon capital temps</a></li>
                  <li><a href="">Ma consommation</a></li>
                  <li className="separator"></li>
                  <li><a href="">Mon compte</a></li>
                  <li className="separator"></li>
                  <li><a href="">Paramètres</a></li>
                  <li><a href="/contact">Nous contacter</a></li>
                </ul>
              </li>
              <li>
                <a className="dropdown-toggler" href="" onClick={handleLogout}>
                  {/* faire en sorte de vider la session de l'utilisateur au clic
                  il sera automatiquement redirigé vers la racine / */}
                  <Link to="/sign-in">Se déconnecter</Link>
                </a>
              </li>
            </ul>
          </div>
        </div>
      </nav>

      <h1 style={{
        fontSize: '2rem',
        textAlign: 'center',
        color: '#333',
        marginBottom: '1rem'
      }}>Capital temps</h1>
      {userQuota !== null && (
        <p style={{
          fontSize: '1.25rem',
          textAlign: 'center',
          color: '#555',
          marginTop: '0'
        }}>
          Voici votre capital temps actuel : {userQuota} heure(s)
        </p>
      )}

    </div>
  );
}

export default UserTimeCapital;
