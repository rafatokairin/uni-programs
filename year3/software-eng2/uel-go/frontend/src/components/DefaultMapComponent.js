import React, { useEffect, useRef } from 'react';
import L from 'leaflet';
import 'leaflet/dist/leaflet.css';

const DefaultMapComponent = ({handleSearch}) => {
  const mapRef = useRef(null);

  useEffect(() => {
    const mapInstance = L.map('default-map', { zoomControl: false }).setView([-23.32623, -51.20164], 20);

    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
      attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
    }).addTo(mapInstance);

    mapInstance.on('click', async (e) => {
      const { lat, lng } = e.latlng;
      try {
        const response = await fetch(`http://localhost:8080/reverse?lat=${lat}&long=${lng}`);
        if (response.ok) {
          const local = await response.json();
          handleSearch(local.name); // Use o nome do local para realizar a busca
        } else {
          console.error('Local não encontrado.');
        }
      } catch (error) {
        console.error('Erro ao realizar a busca reversa:', error);
      }
    });

    mapRef.current = mapInstance;

    return () => {
      mapInstance.remove();
    };
  }, []);

  return <div id="default-map" style={{ height: '100vh', width: '100%' }}></div>;
};

export default DefaultMapComponent;
