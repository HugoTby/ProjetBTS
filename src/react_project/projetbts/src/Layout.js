import React from 'react';
import Navigation from './components/Navigation';
import Footer from './components/Footer';

const Layout = ({ children }) => {
  return (
    <>
      <Navigation />
      {children}
      <Footer />
    </>
  );
};

export default Layout;
