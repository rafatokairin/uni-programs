import React, { useEffect, useRef} from 'react';
import L from 'leaflet';
import 'leaflet/dist/leaflet.css';
import 'leaflet-routing-machine/dist/leaflet-routing-machine.css'; // Folha de estilo do Leaflet Routing Machine
import 'leaflet-control-geocoder/dist/Control.Geocoder.css'; // Folha de estilo do leaflet-control-geocoder
import 'leaflet-routing-machine'; // Importar o controle de roteamento
import 'leaflet-control-geocoder'; // Importar o controle de geocodificação
import mapPinIcon from '../assets/green-pin.png';

const MapComponent = ({ lat, lng, handleSearch }) => {
  const mapRef = useRef(null);

  useEffect(() => {
    if (!mapRef.current) {
      mapRef.current = L.map('map', { zoomControl: false }).setView([lat, lng], 20  );

      L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
      }).addTo(mapRef.current);
    }

    mapRef.current.on('click', async (e) => {
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

    // Clear previous markers and routes
    mapRef.current.eachLayer(layer => {
      if (layer instanceof L.Marker || layer instanceof L.Routing.Control) {
        mapRef.current.removeLayer(layer);
      }
    });

    // Add the new marker for the destination
    L.marker([lat, lng], { icon: L.icon({ iconUrl: mapPinIcon, iconSize: [32, 32] }) }).addTo(mapRef.current);

    return () => {
      if (mapRef.current) {
        mapRef.current.remove();
        mapRef.current = null;
      }
    };
  }, [lat, lng]); 

  return <div id="map" style={{ height: '100%', width: '100%' }}></div>;
};

export default MapComponent;