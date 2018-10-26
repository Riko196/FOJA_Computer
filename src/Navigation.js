// @flow
import React, { Component } from "react";
import { NavLink, withRouter } from "react-router-dom";
import { NavItem, Nav } from "reactstrap";

import "./Navigation.css";

class Navigation extends Component {
  render() {
    return (
      <Nav className="navbar">
        <NavItem className="navitem">
          <NavLink to="/" className="nav-link">
            Home
          </NavLink>
        </NavItem>
        <NavItem className="navitem">
          <NavLink to="/Gramatiky" className="nav-link">
            Gramatiky
          </NavLink>
        </NavItem>
        <NavItem className="navitem">
          <NavLink to="/Automaty" className="nav-link">
            Automaty
          </NavLink>
        </NavItem>
        <NavItem className="navitem">
          <NavLink to="/Turingove_stroje" className="nav-link">
            Turingove stroje
          </NavLink>
        </NavItem>
      </Nav>
    );
  }
}

export default withRouter(Navigation);
