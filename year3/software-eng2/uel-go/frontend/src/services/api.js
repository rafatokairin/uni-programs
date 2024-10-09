import axios from 'axios';

const api = axios.create({
  baseURL: 'http://localhost:8080', // URL do backend, ajuste se necessário
});

export const fetchLocal = async (name) => {
  try {
    const response = await api.get(`/local`, {
      params: { name },
    });
    return response.data;
  } catch (error) {
    console.error("Erro ao buscar o local:", error);
    throw error;
  }
};