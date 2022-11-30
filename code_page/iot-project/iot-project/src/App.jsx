import React from "react";
import NavBar from "./NavBar";
import Nosotros from "./pages/Nosotros";
import Home from './pages/Home'
import { Route, Routes } from "react-router-dom";

export default function App() {
  return (
    <>
      <NavBar />
      <div>
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/nosotros" element={<Nosotros />} />
        </Routes>
      </div>
    </>
  );
}
