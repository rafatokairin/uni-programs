import React, { useEffect, useRef, useState } from 'react';
import L from 'leaflet';
import 'leaflet-routing-machine';
import 'leaflet/dist/leaflet.css';
import locate from 'leaflet.locatecontrol'; 
import mapPinIcon from '../assets/green-pin.png';
import bluePoint from '../assets/blue-point.png';

const RouteMapComponent = ({ end }) => {
  const mapRef = useRef(null);
  const routingControlRef = useRef(null);
  const [routeStart, setRouteStart] = useState(null);

  useEffect(() => {
    const getCurrentLocation = () => {
      if (navigator.geolocation) {
        navigator.geolocation.getCurrentPosition(
          (position) => {
            setRouteStart({   
              lat: position.coords.latitude,
              lng: position.coords.longitude,
            });
          },
          (error) => {
            console.error('Erro ao obter localização:', error);
          },
          {
            enableHighAccuracy: true, // Solicita alta precisão
            timeout: 10000, // Tempo máximo para tentar obter a localização (10 segundos)
            maximumAge: 0 // Não usar uma localização armazenada em cache
          }
        );  
      } else {
        console.error('Geolocalização não é suportada pelo navegador.');  
      }
    };

    getCurrentLocation();
  }, []);

  useEffect(() => {
    if (routeStart) {
      mapRef.current = L.map('route-map', { zoomControl: false }).setView([routeStart.lat, routeStart.lng], 20);
      L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
      }).addTo(mapRef.current);

      return () => {
        if (mapRef.current) {
          mapRef.current.remove();
        }
      };
    }
  }, [routeStart]);

  useEffect(() => {
    if (mapRef.current && routeStart && end) {
      if (routingControlRef.current) {
        routingControlRef.current.getPlan().setWaypoints([]);
        mapRef.current.removeControl(routingControlRef.current);
      }

      L.marker([routeStart.lat, routeStart.lng], { icon: L.icon({ iconUrl: bluePoint, iconSize: [16, 16] }) }).addTo(mapRef.current);
      L.marker([end.lat, end.lng], { icon: L.icon({ iconUrl: mapPinIcon, iconSize: [32, 32] }) }).addTo(mapRef.current);

      routingControlRef.current = L.Routing.control({
        waypoints: [
          L.latLng(routeStart.lat, routeStart.lng),
          L.latLng(end.lat, end.lng)
        ],
        createMarker: () => null,
        show: false,
        lineOptions: {
          styles: [{ color: 'red', opacity: 1, weight: 5 }],
          missingRouteStyles: [{ color: 'red', opacity: 1, weight: 5 }],
          addWaypoints: false
        },
        router: new L.Routing.OSRMv1({
          serviceUrl: 'https://router.project-osrm.org/route/v1'
        })
      }).addTo(mapRef.current);
    }
  }, [routeStart, end]);

  return <div id="route-map" style={{ height: '100%', width: '100%' }}></div>;
};

export default RouteMapComponent;
