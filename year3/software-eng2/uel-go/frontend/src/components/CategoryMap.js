import React, { useEffect, useRef } from 'react';
import L from 'leaflet';
import 'leaflet/dist/leaflet.css';
import mapPinIcon from '../assets/green-pin.png';

const CategoryMap = ({ category, handleSearch }) => {
  const mapRef = useRef(null);

  useEffect(() => {
    if (!category) return;

    const fetchCategoryData = async () => {
      try {
        const response = await fetch(`http://localhost:8080/category?ty=${category}`);
        const data = await response.json();

        if (mapRef.current) {
          mapRef.current.eachLayer(layer => {
            if (layer instanceof L.Marker) {
              mapRef.current.removeLayer(layer);
            }
          });

          data.forEach(local => {
            L.marker([local.lat, local.long], { 
              icon: L.icon({ iconUrl: mapPinIcon, iconSize: [32, 32] }) 
            }).addTo(mapRef.current);
          });
        }
      } catch (error) {
        console.error('Error fetching category data:', error);
      }
    };

    if (!mapRef.current) {
      mapRef.current = L.map('category-map', { zoomControl: false }).setView([-23.325441, -51.201807], 20);

      L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
      }).addTo(mapRef.current);

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
    }

    fetchCategoryData();

    return () => {
      if (mapRef.current) {
        mapRef.current.remove();
        mapRef.current = null;
      }
    };
  }, [category]);

  return <div id="category-map" style={{ height: '100%', width: '100%' }}></div>;
};

export default CategoryMap;
