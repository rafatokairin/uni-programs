package uel.br.Prova1Admin;

import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;
import java.util.List;

@Controller
public class ItemCardapioController {

    @Autowired
    ItemCardapioRepository itemCardapioRepository;
    @Autowired
    RestauranteRepository restauranteRepository;

    @GetMapping("/index-cardapio/{id}")
    public String mostrarListaCardapios(@PathVariable("id") int restauranteId, Model model) {
        Restaurante restaurante = restauranteRepository.findById(restauranteId)
                .orElseThrow(() -> new IllegalArgumentException("O id do restaurante é inválido:" + restauranteId));
        List<ItemCardapio> cardapios = itemCardapioRepository.findByRestauranteId(restauranteId);
        model.addAttribute("restaurante", restaurante);
        model.addAttribute("cardapios", cardapios);
        return "index-cardapio";
    }

    @GetMapping("/novo-cardapio/{id}")
    public String mostrarFormNovoCardapio(@PathVariable("id") int restauranteId, Model model) {
        Restaurante restaurante = restauranteRepository.findById(restauranteId)
                .orElseThrow(() -> new IllegalArgumentException("O id do restaurante é inválido:" + restauranteId));
        model.addAttribute("restaurante", restaurante);
        model.addAttribute("cardapio", new ItemCardapio());
        return "novo-cardapio";
    }

    @PostMapping("/adicionar-cardapio/{id}")
    public String adicionarCardapio(@PathVariable("id") int restauranteId,
                                    @Valid ItemCardapio cardapio,
                                    BindingResult result,
                                    Model model) {
        if (result.hasErrors()) {
            return "novo-cardapio";
        }
        Restaurante restaurante = restauranteRepository.findById(restauranteId)
                .orElseThrow(() -> new IllegalArgumentException("O id do restaurante é inválido:" + restauranteId));
        cardapio.setRestaurante(restaurante);
        itemCardapioRepository.save(cardapio);
        return "redirect:/index-cardapio/" + restauranteId;
    }

    @GetMapping("/{restauranteId}/editar-cardapio/{cardapioId}")
    public String mostrarFormAtualizarCardapio(@PathVariable("restauranteId") int restauranteId,
                                               @PathVariable("cardapioId") int cardapioId,
                                               Model model) {
        Restaurante restaurante = restauranteRepository.findById(restauranteId).orElseThrow(() -> new IllegalArgumentException("O id do restaurante é inválido:" + restauranteId));
        ItemCardapio cardapio = itemCardapioRepository.findById(cardapioId).orElseThrow(() -> new IllegalArgumentException("O id do cardápio é inválido:" + cardapioId));
        model.addAttribute("restaurante", restaurante);
        model.addAttribute("cardapio", cardapio);
        return "atualizar-cardapio";
    }

    @PostMapping("/{restauranteId}/atualizar-cardapio/{cardapioId}")
    public String atualizarCardapio(@PathVariable("restauranteId") int restauranteId,
                                    @PathVariable("cardapioId") int cardapioId,
                                    @Valid ItemCardapio cardapio,
                                    BindingResult result,
                                    Model model) {
        if (result.hasErrors()) {
            cardapio.setId(cardapioId);
            return "atualizar-cardapio";
        }

        ItemCardapio cardapioExistente = itemCardapioRepository.findById(cardapioId).orElseThrow(() -> new IllegalArgumentException("O id do cardápio é inválido:" + cardapioId));

        cardapioExistente.setNome(cardapio.getNome());
        cardapioExistente.setDescricao(cardapio.getDescricao());
        cardapioExistente.setPreco(cardapio.getPreco());
        itemCardapioRepository.save(cardapioExistente);
        return "redirect:/index-cardapio/" + restauranteId;
    }


    @GetMapping("/{restauranteId}/remover-cardapio/{cardapioId}")
    public String removerCardapio(@PathVariable("restauranteId") int restauranteId,
                                  @PathVariable("cardapioId") int cardapioId) {
        itemCardapioRepository.deleteById(cardapioId);
        return "redirect:/index-cardapio/" + restauranteId;
    }
}
