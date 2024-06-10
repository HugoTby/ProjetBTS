import React from 'react';
import '../index.css';

function Footer() {
    return (
        <footer className="site-footer">
            <div className="container3">
                <div className="row">
                    <div className="col-sm-12 col-md-6">
                        <h6>A propos</h6>
                        <p className="text-justify">Lycée Privé la Providence<br />146 boulevard St Quentin, 80090 Amiens, Hauts-de-France, France<br />Tel : (+33) 3 22 33 77 77 <br />Mail : laprovidence.amiens@ac-amiens.fr</p>
                    </div>

                    <div className="col-xs-6 col-md-3">
                        <h6>Divers</h6>
                        <ul className="footer-links">
                            <li><a href="test">Mentions légales</a></li>
                            <li><a href="test">Conditions générales d'utilisation</a></li>
                            <li><a href="test">Politique de confidentialité</a></li>
                        </ul>
                    </div>
                </div>
                <hr />
            </div>
            <div className="container3">
                <div className="row">
                    <div className="col-md-8 col-sm-6 col-xs-12">
                        <p className="copyright-text">Copyright &copy; 2024 tout droits réservés par
                            <a target='blank' href="https://www.la-providence.net/fr/"> La Providence Amiens</a>.
                        </p>
                    </div>

                    <div className="col-md-4 col-sm-6 col-xs-12">
                        <ul className="social-icons">
                            <li><a className="facebook" target='blank' href="https://www.facebook.com/La-Providence-Amiens-717439835438761"><i className="fa fa-facebook"></i></a></li>
                            <li><a className="twitter" target='blank' href="https://twitter.com/ecolelapro80"><i className="fa fa-twitter"></i></a></li>
                            <li><a className="youtube" target='blank' href="https://www.youtube.com/channel/UCSd0QtFgyxn-ZdQLgK36yVg"><i className="fa fa-youtube"></i></a></li>
                            <li><a className="linkedin" target='blank' href="https://www.linkedin.com/school/laprovidence-amiens/"><i className="fa fa-linkedin"></i></a></li>
                        </ul>
                    </div>
                </div>
            </div>
        </footer>
    );
}

export default Footer;
