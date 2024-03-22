import React, { useState, useEffect } from 'react';
import { Link } from 'react-router-dom';
import './css/main.css';
import './js/script.js';

function UserMain() {

    const [dropdownIsOpen, setDropdownIsOpen] = useState(false);

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



    const handleOutsideClick = (event) => {
        if (dropdownIsOpen && !event.target.closest('.navbar-dropdown')) {
            setDropdownIsOpen(false);
            document.querySelector('.dropdown.show').classList.remove('show');
        }
    };

    useEffect(() => {
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
            <nav className="navbar">
                <div className="container">
                    <div className="navbar-header">
                        <button className="navbar-toggler" data-toggle="open-navbar1">
                            <span></span>
                            <span></span>
                            <span></span>
                        </button>
                        <a href="">
                            <h4>La Providence <span>Amiens</span></h4>
                        </a>
                    </div>

                    <div className="navbar-menu" id="open-navbar1">
                        <ul className="navbar-nav">
                            <li className="active"><a href="">Accueil</a></li>
                            <li className="navbar-dropdown">
                                <a href="" className="dropdown-toggler" data-dropdown="my-dropdown-id">
                                    Catégories <i className="fa fa-angle-down"></i>
                                </a>
                                <ul className="dropdown" id="my-dropdown-id">
                                    <li><a href="/test">Actions</a></li>
                                    <li><a href="">Something else here</a></li>
                                    <li className="separator"></li>
                                    <li><a href="">Seprated link</a></li>
                                    <li className="separator"></li>
                                    <li><a href="">One more seprated link.</a></li>
                                </ul>
                            </li>
                            <li><a className="dropdown-toggler2" href="/about">A Propos</a></li>
                            <li><a className="dropdown-toggler2" href="/contact">Nous contacter</a></li>
                            <li>
                                <a className="dropdown-toggler" href="">
                                    {/* faire en sorte de vider la session de l'utilisateur au clic
                                    il sera automatiquement redirigé vers la racine / */}
                                    <Link to="/">Se déconnecter</Link>
                                </a>
                            </li>
                        </ul>
                    </div>
                </div>
            </nav>
        </div>
    );
}

export default UserMain;
