import React, { useState, useEffect } from 'react';
import { fetchLocal } from '../services/api';
import MapComponent from './MapComponent';
import DefaultMapComponent from './DefaultMapComponent';
import Popup from './Popup';
import CategoryMap from './CategoryMap';
import RouteMapComponent from './RouteMapComponent';
import './Search.css'; // Importação dos estilos

// Função para normalizar a string conforme requisitos
const normalizeString = (input) => {

  // Palavras para eliminar
  const stopWords = new Set(['de', 'do', 'da', 'e', 'a', 'o', 'para', 'em', 'com', 'por']);

  // Normaliza a string
  return input
    .toLowerCase()                   // Converte para minúsculas
    .normalize('NFD')                // Remove acentuação
    .replace(/[\u0300-\u036f]/g, '') // Remove diacríticos (acentos)
    .split(' ')                      // Separa por espaços
    .filter(word => !stopWords.has(word)) // Remove palavras específicas
    .join(' ')                       // Junta novamente por espaços
    .trim()                          // Remove espaços no início e no final
    .replace(/\s+/g, '-')            // Substitui espaços por hífens
}

let itemList = [];

// Componente Search
const Search = () => {
  const [name, setName] = useState('');
  const [local, setLocal] = useState(null);
  const [error, setError] = useState(null);
  const [showPopup, setShowPopup] = useState(false);
  const [category, setCategory] = useState(null);
  const [categoryData, setCategoryData] = useState([]);
  const [showRouteMap, setShowRouteMap] = useState(false); // Estado para exibir o mapa de rotas
  const [routeStart, setRouteStart] = useState(null); // Coordenadas de início da rota
  const [routeEnd, setRouteEnd] = useState(null); // Coordenadas de fim da rota
  const [pathIcon, setPathIcon] = useState('M480-528 296-344l-56-56 240-240 240 240-56 56-184-184Z');
  const [listController, setListController] = useState(false);

// Estrutura do item
class Item {
  constructor(name, img_path, display_name) {
    this.name = name;
    this.img_path = img_path; 
    this.display_name = display_name;
  }
}

// Função para inserir um item na lista
function addItem(name, img_path, display_name) {
  const newItem = new Item(name, img_path, display_name);
  itemList.push(newItem);
}

// Função para remover um item da lista pelo nome
function removeItem(name) {
  itemList = itemList.filter(item => item.name !== name);
}

// Função para conferir se um item está na lista pelo nome
function hasItem(name) {
  return itemList.some(item => item.name === name);
} 

const displayItemNames = (items) => {
  items.forEach(item => console.log(item.name));
};

const handleSaveLocal = (name, img_path, display_name) => {
  setListController(false);
  if (hasItem(name)) {
    // setPathIcon('M200-120v-640q0-33 23.5-56.5T280-840h240v80H280v518l200-86 200 86v-278h80v400L480-240 200-120Zm80-640h240-240Zm400 160v-80h-80v-80h80v-80h80v80h80v80h-80v80h-80Z')
    removeItem(name);
    displayItemNames(itemList)
  }
  else {
    // setP athIcon('M713-600 600-713l56-57 57 57 141-142 57 57-198 198ZM200-120v-640q0-33 23.5-56.5T280-840h240v80H280v518l200-86 200 86v-278h80v400L480-240 200-120Zm80-640h240-240Z')
    addItem(name, img_path, display_name);
    displayItemNames(itemList)
  }
}


  const handleSearch = async (searchName) => {
    const normalizedSearchName = normalizeString(searchName);
    
    try {
      const result = await fetchLocal(normalizedSearchName);
      setLocal(result);
      setError(null);
      setShowPopup(false); // Fechar o popup se a pesquisa for bem-sucedida
      setCategory(null);
      setRouteStart({ lat: -23.326264, lng: -51.201857 }); // Defina as coordenadas de início padrão
      setRouteEnd({ lat: result.lat, lng: result.long }); // Defina o ponto final da rota como o local pesquisado
      setShowRouteMap(false);
      // if (!hasItem(name)) setPathIcon('M200-120v-640q0-33 23.5-56.5T280-840h240v80H280v518l200-86 200 86v-278h80v400L480-240 200-120Zm80-640h240-240Zm400 160v-80h-80v-80h80v-80h80v80h80v80h-80v80h-80Z')
      // else setPathIcon('M713-600 600-713l56-57 57 57 141-142 57 57-198 198ZM200-120v-640q0-33 23.5-56.5T280-840h240v80H280v518l200-86 200 86v-278h80v400L480-240 200-120Zm80-640h240-240Z')
    } catch (err) {
      setError(`O local "${name}" não foi encontrado. Tem certeza que esse local existe, ou foi escrito corretamente?`);
      setShowPopup(true); // Mostrar o popup em caso de erro
    }
  };

  const handleClosePopup = () => {
    setShowPopup(false);
  };

  const handleClearSearch = () => {
    setName('');
    setLocal(null);
    setError(null);
    setShowPopup(false);
    setCategory(null);
    setShowRouteMap(false); // Oculta o mapa de rotas
  };

  const handleCategorySelect = async (selectedCategory) => {
    setCategory(selectedCategory);
    setName('');
    setLocal(null); // Limpa as informações do local
    setError(null);
    setShowPopup(false);
    setShowRouteMap(false);

    try {
      const response = await fetch(`http://localhost:8080/category?ty=${selectedCategory}`);
      const data = await response.json();
      setCategoryData(data);
    } catch (error) {
      console.error('Error fetching category data:', error);
    }
  };

  const handleGenerateRoute = () => {
    setShowRouteMap(true); // Exibe o mapa de rotas
    setError(null);
    setShowPopup(false);
    setCategory(null);
  };

  const handleTurnOnOffController = () => {
    if (listController) {
      setPathIcon('M480-528 296-344l-56-56 240-240 240 240-56 56-184-184Z')
      setListController(false)
    }
    else {
      setPathIcon('M480-344 240-584l56-56 184 184 184-184 56 56-240 240Z')
      setListController(true)
    }
  }

  const categoryNames = {
    banheiro: 'Banheiros',
    pet: 'PET',
    secretaria: 'secretaria',
    sala: 'Salas',
    departamento: 'Departamentos',
    centro: 'Centros',
    restaurante: 'Restaurantes'
  };



  return (
    <div className="search-container">
      
      
      <div className="search-content">
        <div className="search-bar">
          <div className='barra'>
            <input
              type="text"
              value={name}
              onChange={(e) => setName(e.target.value)}
              placeholder="Pesquisar localização  "
            />
            <button onClick={() => handleSearch(name)}>
              <svg xmlns="http://www.w3.org/2000/svg" height="20px" viewBox="0 -1060 1060 960" width="20px" fill="black">
                <path d="M784-120 532-372q-30 24-69 38t-83 14q-109 0-184.5-75.5T120-580q0-109 75.5-184.5T380-840q109 0 184.5 75.5T640-580q0 44-14 83t-38 69l252 252-56 56ZM380-400q75 0 127.5-52.5T560-580q0-75-52.5-127.5T380-760q-75 0-127.5 52.5T200-580q0 75 52.5 127.5T380-400Z"/>
              </svg>
            </button>
            <button onClick={handleClearSearch}>
              <svg xmlns="http://www.w3.org/2000/svg" height="20px" viewBox="0 -1060 960 960" width="20px" fill="black"><path d="m291-240-51-51 189-189-189-189 51-51 189 189 189-189 51 51-189 189 189 189-51 51-189-189-189 189Z"/></svg>
            </button>
          </div>
          <ul className='listCategory'>
            <li onClick={() => handleCategorySelect('centro')} className='localCategory'><svg xmlns="http://www.w3.org/2000/svg" height="16px" viewBox="0 -1060 960 960" width="24px" fill="black"><path d="M96-144v-672h384v144h384v528H96Zm72-72h72v-72h-72v72Zm0-152h72v-72h-72v72Zm0-152h72v-72h-72v72Zm0-152h72v-72h-72v72Zm168 456h72v-72h-72v72Zm0-152h72v-72h-72v72Zm0-152h72v-72h-72v72Zm0-152h72v-72h-72v72Zm144 456h312v-384H480v80h72v72h-72v80h72v72h-72v80Zm168-232v-72h72v72h-72Zm0 152v-72h72v72h-72Z"/></svg>Centros</li>
            <li onClick={() => handleCategorySelect('departamento')} className='localCategory'><svg xmlns="http://www.w3.org/2000/svg" height="16px" viewBox="0 -1060 960 960" width="24px" fill="black"><path d="M96-192v-92q0-25.78 12.5-47.39T143-366q54-32 114.5-49T384-432q66 0 126.5 17T625-366q22 13 34.5 34.61T672-284v92H96Zm648 0v-92q0-42-19.5-78T672-421q39 8 75.5 21.5T817-366q22 13 34.5 34.67Q864-309.65 864-284v92H744ZM384-480q-60 0-102-42t-42-102q0-60 42-102t102-42q60 0 102 42t42 102q0 60-42 102t-102 42Zm336-144q0 60-42 102t-102 42q-8 0-15-.5t-15-2.5q25-29 39.5-64.5T600-624q0-41-14.5-76.5T546-765q8-2 15-2.5t15-.5q60 0 102 42t42 102ZM168-264h432v-20q0-6.47-3.03-11.76-3.02-5.3-7.97-8.24-47-27-99-41.5T384-360q-54 0-106 14t-99 42q-4.95 2.83-7.98 7.91-3.02 5.09-3.02 12V-264Zm216.21-288Q414-552 435-573.21t21-51Q456-654 434.79-675t-51-21Q354-696 333-674.79t-21 51Q312-594 333.21-573t51 21ZM384-264Zm0-360Z"/></svg>Departamentos</li>
            <li onClick={() => handleCategorySelect('sala')} className='localCategory'><svg xmlns="http://www.w3.org/2000/svg" height="16px" viewBox="0 -1060 960 960" width="24px" fill="black"><path d="M480-144 216-276v-240L48-600l432-216 432 216v312h-72v-276l-96 48v240L480-144Zm0-321 271-135-271-135-271 135 271 135Zm0 240 192-96v-159l-192 96-192-96v159l192 96Zm0-240Zm0 81Zm0 0Z"/></svg>Salas</li>
            <li onClick={() => handleCategorySelect('secretaria')} className='localCategory'><svg xmlns="http://www.w3.org/2000/svg" height="16px" viewBox="0 -1060 960 960" width="24px" fill="black"><path d="M320-240h320v-80H320v80Zm0-160h320v-80H320v80ZM240-80q-33 0-56.5-23.5T160-160v-640q0-33 23.5-56.5T240-880h320l240 240v480q0 33-23.5 56.5T720-80H240Zm280-520v-200H240v640h480v-440H520ZM240-800v200-200 640-640Z"/></svg>Secretaria</li>
            <li onClick={() => handleCategorySelect('pet')} className='localCategory'><svg xmlns="http://www.w3.org/2000/svg" height="16px" viewBox="0 -1060 960 960" width="24px" fill="black"><path d="M480-72q-69-64-155.22-104T144-216v-384q95 0 179.5 39T480-456q72-66 156.5-105T816-600v384q-95.49 0-181.24 40Q549-136 480-72Zm0-95q59-44 125-75t139-41v-237q-78 14-142.5 59.5T480-358q-57-57-121.5-102.5T216-520v237q73 9 139 40.5T480-167Zm0-385q-70 0-119-49t-49-119q0-70 49-119t119-49q70 0 119 49t49 119q0 70-49 119t-119 49Zm0-72q39.6 0 67.8-28.2Q576-680.4 576-720q0-39.6-28.2-67.8Q519.6-816 480-816q-39.6 0-67.8 28.2Q384-759.6 384-720q0 39.6 28.2 67.8Q440.4-624 480-624Zm0-96Zm0 362Z"/></svg>PET</li>
            <li onClick={() => handleCategorySelect('banheiro')} className='localCategory'><svg xmlns="http://www.w3.org/2000/svg" height="16px" viewBox="0 -1060 960 960" width="24px" fill="black"><path d="M220-80v-300h-60v-220q0-33 23.5-56.5T240-680h120q33 0 56.5 23.5T440-600v220h-60v300H220Zm80-640q-33 0-56.5-23.5T220-800q0-33 23.5-56.5T300-880q33 0 56.5 23.5T380-800q0 33-23.5 56.5T300-720ZM600-80v-240H480l102-306q8-26 29.5-40t48.5-14q27 0 48.5 14t29.5 40l102 306H720v240H600Zm60-640q-33 0-56.5-23.5T580-800q0-33 23.5-56.5T660-880q33 0 56.5 23.5T740-800q0 33-23.5 56.5T660-720Z"/></svg>Banheiros</li>
            <li onClick={() => handleCategorySelect('restaurante')} className='localCategory'><svg xmlns="http://www.w3.org/2000/svg" height="16px" viewBox="0 -1060 960 960" width="24px" fill="black"><path d="M280-80v-366q-51-14-85.5-56T160-600v-280h80v280h40v-280h80v280h40v-280h80v280q0 56-34.5 98T360-446v366h-80Zm400 0v-320H560v-280q0-83 58.5-141.5T760-880v800h-80Z"/></svg>Restaurantes</li>
          </ul>
        </div>
        <div className='favoriteList'>
          <button onClick={() => handleTurnOnOffController()}>
            <svg xmlns="http://www.w3.org/2000/svg" height="30px" viewBox="0 -1020 960 960" width="30px" fill="black"><path d={pathIcon}/></svg>
          </button>
        </div>

        <div className="search-map">
        {category ? (
          <CategoryMap category={category} handleSearch={handleSearch}/>
        ) : showRouteMap ? (
          <RouteMapComponent end={routeEnd} />
        ) : local ? (
          <MapComponent lat={local.lat} lng={local.long} handleSearch={handleSearch}/>
        ) : (
          <DefaultMapComponent handleSearch={handleSearch}/>
        )}
      </div>

        {local && !showRouteMap && (
          <div className="search-info">
            {local.salvo = true}
            {local.img_path && (
              <img
                src={`img/${local.img_path}?${new Date().getTime()}`} 
                alt={local.name}
                style={{ width: '400px', height: '400px' }} 
              />
            )}
            <p>{local.display_name}</p>
            <p>{local.ty}</p>
            <div className='botoes'>
              <button onClick={() => handleGenerateRoute()}><svg xmlns="http://www.w3.org/2000/svg" height="30px" viewBox="25 -1025 960 960" width="30px" fill="green"><path d="M336-384h72v-96h120v84l120-120-120-120v84H371.76q-14.76 0-25.26 10.35Q336-531.3 336-516v132ZM480-96q-13.64 0-26.82-5T429-117L117-429q-11-11-16-24.18T96-480q0-13.64 5-26.82T117-531l312-312q11-11 24.18-16t26.82-5q13.64 0 26.82 5T531-843l312 312q11 11 16 24.18t5 26.82q0 13.64-5 26.82T843-429L531-117q-11 11-24.18 16T480-96ZM324-324l156 156 312-312-312-312-312 312 156 156Zm156-156Z"/></svg></button>
              
              {true && (
                <button id='safeButton' onClick={() => handleSaveLocal(local.name, local.img_path, local.display_name)}>
                  <svg xmlns="http://www.w3.org/2000/svg" height="30px" viewBox="40 -1040 960 960" width="30px" fill="#e8eaed">
                    <path d='M200-120v-640q0-33 23.5-56.5T280-840h240v80H280v518l200-86 200 86v-278h80v400L480-240 200-120Zm80-640h240-240Zm400 160v-80h-80v-80h80v-80h80v80h80v80h-80v80h-80Z'/>
                  </svg>
                </button>
              )}

              {/* {hasItem(local.name) && (
                <button id='safeButton' onClick={() => handleSaveLocal(local.name)}>
                  <svg xmlns="http://www.w3.org/2000/svg" height="30px" viewBox="40 -1040 960 960" width="30px" fill="#e8eaed">
                    <path d='M713-600 600-713l56-57 57 57 141-142 57 57-198 198ZM200-120v-640q0-33 23.5-56.5T280-840h240v80H280v518l200-86 200 86v-278h80v400L480-240 200-120Zm80-640h240-240Z'/>
                  </svg>
                </button>
              )} */}

            </div>
            <p>{local.description}</p>
          </div>
        )}

          {category && (
            <div className="category-info-scrollable">
              <h2>{categoryNames[category]}</h2>
              {categoryData.map(local => (
                <div key={local.id} className="category-item">
                  <p onClick={() => handleSearch(local.name)}>{local.display_name}</p>
                  {local.img_path && (
                    <img
                      src={`img/${local.img_path}`}
                      alt={local.name}
                      style={{ width: '100px', height: '100px' }}
                    />
                  )}
                </div>
              ))}
            </div>
          )}

          {listController && (
            <div className='savedLocais'>

              {itemList.length <= 0 && (
                <p className='emptyList'>Não há locais salvos</p>
              )}

              {itemList.length > 0 && (
                <div className='savedItemDiv'>
                  {itemList.map(item => (
                    <div key={item.name} className='savedItem' onClick={() => handleSearch(item.name)}>
                      {item.display_name}
                    </div>
                  ))}
                </div>
              )}

            </div>
          )}

          {local && showRouteMap &&  (
          <div className="search-info">
            {local.salvo = true}
            {local.img_path && (
              <img
                src={`img/${local.img_path}?${new Date().getTime()}`} 
                alt={local.name}
                style={{ width: '400px', height: '400px' }}
              />
            )}
            <p>{local.display_name}</p>
            <p>{local.ty}</p>
            <button onClick={() => handleSearch(local.name)}><svg xmlns="http://www.w3.org/2000/svg" height="30px" viewBox="0 -1035 960 960" width="30px" fill="green"><path d="m291-240-51-51 189-189-189-189 51-51 189 189 189-189 51 51-189 189 189 189-51 51-189-189-189 189Z"/></svg></button>
            <p>{local.description}</p>
          </div>
        )}



        {showPopup && (
          <Popup onClose={handleClosePopup}>
            <p>{error}</p>
            <a href={`https://www.google.com/search?q=${encodeURIComponent(name)}`} target="_blank" rel="noopener noreferrer">
              Tente usar a Pesquisa Google
            </a>
          </Popup>
        )}
      </div>
    </div>
  );
};

export default Search;
