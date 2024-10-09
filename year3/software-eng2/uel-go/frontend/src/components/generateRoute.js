import L from 'leaflet';
import 'leaflet-routing-machine';

const generateRoute = async (startLat, startLng, endLat, endLng) => {
  return new Promise((resolve, reject) => {
    try {
      // Inicializa o mapa
      const map = L.map('map').setView([startLat, startLng], 13);

      L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
      }).addTo(map);

      // Adiciona o controle de rota
      L.Routing.control({
        waypoints: [
          L.latLng(startLat, startLng),
          L.latLng(endLat, endLng)
        ],
        router: new L.Routing.Valhalla({
          serviceUrl: 'http://localhost:8002/route', // URL do seu serviço Valhalla
          profile: 'pedestrian' // Define o perfil para pedestres
        }),
        createMarker: () => null // Remove marcadores padrão
      }).addTo(map);

      resolve();
    } catch (error) {
      reject(error);
    }
  });
};

export default generateRoute;
