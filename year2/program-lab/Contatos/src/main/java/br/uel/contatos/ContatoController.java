package br.uel.contatos;
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
import java.util.List;

@Controller
public class ContatoController {
    private static final String SESSION_FAVORITOS = "sessionFavoritos";
    @Autowired
    ContatoRepository contatoRepository;
    @GetMapping("/novo-contato")
    public String mostrarFormNovoContato(Contato contato){
        return "novo-contato";
    }
    @GetMapping(value={"/index", "/"})
    public String mostrarListaContatos(Model model) {
        model.addAttribute("contatos", contatoRepository.findAll());
        return "index";
    }
    @PostMapping("/adicionar-contato")
    public String adicionarContato(@Valid Contato contato, BindingResult result) {
        if (result.hasErrors()) {
            return "/novo-contato";
        }
        contatoRepository.save(contato);
        return "redirect:/index";
    }
    @GetMapping("/editar/{id}")
    public String mostrarFormAtualizar(@PathVariable("id") int id, Model model) {
        Contato contato = contatoRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException(
                        "O id do contato é inválido:" + id));
        model.addAttribute("contato", contato);
        return "atualizar-contato";
    }
    @PostMapping("/atualizar/{id}")
    public String atualizarContato(@PathVariable("id") int id, @Valid Contato contato,BindingResult result, Model model) {
        if (result.hasErrors()) {
            contato.setId(id);
            return "atualizar-contato";
        }
        contatoRepository.save(contato);
        return "redirect:/index";
    }
    @GetMapping("/remover/{id}")
    public String removerContato(@PathVariable("id") int id, HttpServletRequest request) {
        Contato contato = contatoRepository.findById(id).orElseThrow(() -> new IllegalArgumentException("O id do contato é inválido:" + id));
        contatoRepository.delete(contato);
        List<Contato> sessionFavoritos = (List<Contato>) request.getSession().getAttribute(SESSION_FAVORITOS);
        sessionFavoritos.remove(contato);
        request.getSession().setAttribute(SESSION_FAVORITOS, sessionFavoritos);
        return "redirect:/index";
    }
    @GetMapping("/favoritar/{id}")
    public String favoritarContato(@PathVariable("id") int id, HttpServletRequest request){
        Contato contato = contatoRepository.findById(id).orElseThrow(() -> new IllegalArgumentException("O id do contato é inválido: " + id));
        List<Contato> favoritos = (List<Contato>)request.getSession().getAttribute(SESSION_FAVORITOS);
        if (CollectionUtils.isEmpty(favoritos)) {
            favoritos = new ArrayList<>();
        }
        if (!favoritos.contains(contato)){
            favoritos.add(contato);
        }
        request.getSession().setAttribute(SESSION_FAVORITOS, favoritos);
        return "redirect:/favoritos";
    }
    @GetMapping("/favoritos")
    public String mostrarFavoritos(Model model, HttpServletRequest request){
        List<Contato> favoritos = (List<Contato>) request.getSession().getAttribute(SESSION_FAVORITOS);
        model.addAttribute("sessionFavoritos", !CollectionUtils.isEmpty(favoritos) ? favoritos : new ArrayList<>());
        return "favoritos";
    }
    @GetMapping("/favoritos/remover/{id}")
    public String removerFavorito(@PathVariable("id") int id, HttpServletRequest request) {
        List<Contato> sessionFavoritos = (List<Contato>) request.getSession().getAttribute(SESSION_FAVORITOS);
        Contato contato = contatoRepository.findById(id).orElseThrow(() -> new IllegalArgumentException("O id do contato é inválido: " + id));
        sessionFavoritos.remove(contato);
        request.getSession().setAttribute(SESSION_FAVORITOS, sessionFavoritos);
        return "redirect:/favoritos";
    }
}