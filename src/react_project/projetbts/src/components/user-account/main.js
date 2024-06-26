import React, { useState, useEffect } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import Cookies from 'js-cookie';
import './css/main.css';
import './js/script.js';

function UserMain() {

    const navigate = useNavigate();


    const [dropdownIsOpen, setDropdownIsOpen] = useState(false);
    const [userId, setUserId] = useState(null);

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
        const user = Cookies.get('user');
        if (!user) {
            navigate('/sign-in');
        } else {
            const parsedUser = JSON.parse(user);
            setUserId(parsedUser.id_utilisateur);
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
                                    <li><a href="/consumption">Ma consommation</a></li>
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
            {/* {userId && <p>ID utilisateur : {userId}</p>} */}

            <section id="intro">
                <div class="info">
                    <h1>Bienvenue !</h1>
                    <p>
                    Bienvenue sur votre espace personnel ! Nous sommes ravis de vous compter parmi nos utilisateurs et de vous offrir un espace dédié pour gérer votre compte et vos préférences.
                    </p>
                </div>
                <div class="split-beer">
                    <img
                        class="beer"
                        src="https://github.com/HugoTby/ProjetBTS/blob/main/documents/00.jpg?raw=true" />
                    <img
                        class="beer"
                        src="https://github.com/HugoTby/ProjetBTS/blob/main/documents/10.jpg?raw=true" />
                    <img
                        class="beer"
                        src="https://github.com/HugoTby/ProjetBTS/blob/main/documents/20.jpg?raw=true" />
                </div>
            </section>

            

            <footer>
                <p>
                Notre objectif est de vous fournir une expérience utilisateur fluide et agréable, et nous espérons que vous apprécierez les fonctionnalités et les services que nous avons mis en place pour vous.
                </p>
            </footer>
        </div>
    );
}

export default UserMain;
