import React from 'react';

function Footer() {
    return (

        <footer className="footer">
            <div className="container">
                <div className="row">
                    <div className="col-sm-12 col-md-6">
                        <h6>À propos</h6>
                        <p className="text-justify">
                        Lycée Privé la Providence • 146 boulevard St Quentin - 80090 Amiens • France • (+33) 3 22 33 77 77 • laprovidence.amiens@ac-amiens.fr
                        </p>
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
                <div className="row">
                    <div className="col-md-8 col-sm-6 col-xs-12">
                        <p className="copyright-text">
                            Copyright &copy; 2024 tout droits réservés par
                            <a target="blank" href="https://www.la-providence.net/fr/">
                                La Providence Amiens
                            </a>
                            .
                        </p>
                    </div>

                    <div className="col-md-4 col-sm-6 col-xs-12">
                        <ul className="social-icons">
                            <li>
                                <a className="facebook" href="test">
                                    <i className="fa fa-facebook"></i>
                                </a>
                            </li>
                            <li>
                                <a className="twitter" href="test">
                                    <i className="fa fa-twitter"></i>
                                </a>
                            </li>
                            <li>
                                <a className="dribbble" href="test">
                                    <i className="fa fa-dribbble"></i>
                                </a>
                            </li>
                            <li>
                                <a className="linkedin" href="test">
                                    <i className="fa fa-linkedin"></i>
                                </a>
                            </li>
                        </ul>
                    </div>
                </div>
            </div>
        </footer>


    );
}

export default Footer;
