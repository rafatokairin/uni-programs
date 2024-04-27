package uel.br.Prova1Consumidor;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.util.CollectionUtils;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

@Controller
public class ItemCardapioController {
    @Autowired
    RestauranteRepository restauranteRepository;
    @Autowired
    ItemCardapioRepository cardapioRepository;
    private static final String SESSION_PEDIDO = "sessionPedido";
    private static final String SESSION_VALOR_TOTAL = "sessionValorTotal";

    @GetMapping("/index-cardapio/{id}")
    public String mostrarListaCardapio(@PathVariable("id") int id, Model model) {
        model.addAttribute("cardapios", cardapioRepository.findByRestauranteId(id));
        Restaurante restaurante = restauranteRepository.findById(id).orElse(null);
        model.addAttribute("restaurante", restaurante);
        return "index-cardapio";
    }

    @GetMapping("/pedido")
    public String mostrarPedido(Model model, HttpServletRequest request) {
        List<ItensPedido> pedido = (List<ItensPedido>) request.getSession().getAttribute(SESSION_PEDIDO);

        // Verifica se o item ainda existe no banco de dados, atualiza os valores e adiciona ao pedido
        List<ItensPedido> pedidoValido = new ArrayList<>();
        if (pedido != null) {
            for (ItensPedido p : pedido) {
                ItemCardapio verificaItem = cardapioRepository.findById(p.getId()).orElse(null);
                if (verificaItem != null) {
                    p.setNomeRestaurante(verificaItem.getRestaurante().getNome());
                    p.setNome(verificaItem.getNome());
                    p.setPreco(verificaItem.getPreco());
                    pedidoValido.add(p);
                }
            }
        }

        double valorTotal = calcValorTotal(pedidoValido);

        request.getSession().setAttribute(SESSION_PEDIDO, pedidoValido);
        request.getSession().setAttribute(SESSION_VALOR_TOTAL, valorTotal);

        model.addAttribute("sessionPedido", !CollectionUtils.isEmpty(pedidoValido) ? pedidoValido : new ArrayList<>());
        model.addAttribute("valorTotal", valorTotal);
        return "pedido";
    }

    @GetMapping("/adicionar-pedido/{id}")
    public String adicionarPedido(@PathVariable("id") int id, HttpServletRequest request) {
        ItemCardapio item = cardapioRepository.findById(id).orElseThrow(() -> new IllegalArgumentException("O id do item é inválido:" + id));
        List<ItensPedido> pedido = (List<ItensPedido>)request.getSession().getAttribute(SESSION_PEDIDO);

        if (pedido == null) {
            pedido = new ArrayList<ItensPedido>();
        }

        // Verifica se item já está no pedido
        boolean existeItem = false;
        for (ItensPedido p : pedido) {
            if (p.getId() == item.getId()) {
                existeItem = true;
                p.setQuantidadePedido(1);
                break;
            }
        }
        if (existeItem == false) {
            ItensPedido np = new ItensPedido(item.getId(), item.getNome(), item.getDescricao(), item.getPreco(), item.getRestaurante().getNome());
            pedido.add(np);
        }

        double valorTotal = calcValorTotal(pedido);

        request.getSession().setAttribute(SESSION_PEDIDO, pedido);
        request.getSession().setAttribute(SESSION_VALOR_TOTAL, valorTotal);
        return "redirect:/pedido";
    }

    @GetMapping("/pedido/remover/{id}")
    public String removerPedido(@PathVariable("id") int id, HttpServletRequest request) {
        List<ItensPedido> pedido = (List<ItensPedido>) request.getSession().getAttribute(SESSION_PEDIDO);

        ItemCardapio item = cardapioRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("O id do item é inválido:" + id));

        Iterator<ItensPedido> iterator = pedido.iterator();
        while (iterator.hasNext()) {
            ItensPedido p = iterator.next();
            if (p.getId() == item.getId()) {
                iterator.remove(); // Remove de forma segura usando o iterador
            }
        }

        // Recalcular o valor total após remover o item
        double valorTotal = calcValorTotal(pedido);

        // Remover itens inválidos (que não estão mais no banco de dados)
        Iterator<ItensPedido> pedidoIterator = pedido.iterator();
        while (pedidoIterator.hasNext()) {
            ItensPedido p = pedidoIterator.next();
            if (cardapioRepository.findById(p.getId()).isEmpty()) {
                pedidoIterator.remove();
            }
        }

        // Atualizar a sessão com o pedido atualizado e o valor total
        request.getSession().setAttribute(SESSION_PEDIDO, pedido);
        request.getSession().setAttribute(SESSION_VALOR_TOTAL, valorTotal);

        return "redirect:/pedido";
    }

    // Se quantidade > 1, diminuir; Se quantidade == 1, remove
    @GetMapping("/diminuir/{id}")
    public String diminuirItemPedido (@PathVariable("id") int id, HttpServletRequest request) {
        ItemCardapio item = cardapioRepository.findById(id).orElseThrow(() -> new IllegalArgumentException("O id do item é inválido:" + id));
        List<ItensPedido> pedido = (List<ItensPedido>)request.getSession().getAttribute(SESSION_PEDIDO);

        if (pedido == null) {
            pedido = new ArrayList<ItensPedido>();
        }

        for (ItensPedido p : pedido) {
            if (p.getId() == item.getId()) {
                if (p.getQuantidadePedido() > 1) {
                    p.setQuantidadePedido(-1);
                } else if (p.getQuantidadePedido() == 1) {
                    removerPedido(p.getId(), request);
                }
                break;
            }
        }

        double valorTotal = calcValorTotal(pedido);

        request.getSession().setAttribute(SESSION_PEDIDO, pedido);
        request.getSession().setAttribute(SESSION_VALOR_TOTAL, valorTotal);
        return "redirect:/pedido";
    }
    public double calcValorTotal(List<ItensPedido> pedido) {
        double valorTotal = 0;
        for (ItensPedido p : pedido) {
            valorTotal = valorTotal + (p.getQuantidadePedido() * p.getPreco());
        }
        return valorTotal;
    }
}