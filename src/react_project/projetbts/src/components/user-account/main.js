import React from 'react';
import { Link } from 'react-router-dom';
import './css/main.css';

function UserMain() {

  return (
    <div>
      <button> <Link to="/">Se déconnecter</Link></button>
      <nav className="navbar">
        <div className="container">
          <div className="navbar-header">
            <button className="navbar-toggler" data-toggle="open-navbar1">
              <span></span>
              <span></span>
              <span></span>
            </button>
            <a href="#test">
              <h4>Awesome<span>logo</span></h4>
            </a>
          </div>

          <div className="navbar-menu" id="open-navbar1">
            <ul className="navbar-nav">
              <li className="active"><a href="#test">Home</a></li>
              <li className="navbar-dropdown">
                <a href="#test" className="dropdown-toggler" data-dropdown="my-dropdown-id">
                  Categories <i className="fa fa-angle-down"></i>
                </a>
                <ul className="dropdown" id="my-dropdown-id">
                  <li><a href="#test">Actions</a></li>
                  <li><a href="#test">Something else here</a></li>
                  <li className="separator"></li>
                  <li><a href="#test">Seprated link</a></li>
                  <li className="separator"></li>
                  <li><a href="#test">One more seprated link.</a></li>
                </ul>
              </li>
              <li className="navbar-dropdown">
                <a href="#test" className="dropdown-toggler" data-dropdown="blog">
                  Blog <i className="fa fa-angle-down"></i>
                </a>
                <ul className="dropdown" id="blog">
                  <li><a href="#test">Some category</a></li>
                  <li><a href="#test">Some another category</a></li>
                  <li className="separator"></li>
                  <li><a href="#test">Seprated link</a></li>
                  <li className="separator"></li>
                  <li><a href="#test">One more seprated link.</a></li>
                </ul>
              </li>
              <li><a href="#test">About</a></li>
              <li><a href="#test">Contact</a></li>
              <li><a href="#test">Signin</a></li>
            </ul>
          </div>
        </div>
      </nav>
    </div>
  );
}

export default UserMain;
