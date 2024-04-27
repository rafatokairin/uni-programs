package uel.br.Prova1Consumidor;

import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface ItemCardapioRepository extends JpaRepository<ItemCardapio,Integer> {

    List<ItemCardapio> findByRestauranteId(int id_restaurante);
}
