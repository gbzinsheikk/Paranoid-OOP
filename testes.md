# Relatório de Processo de Testes do Sistema - Paranoid

## 1. Introdução

Este documento relata o processo de validação do sistema, detalhando os testes funcionais, lógicos e de interface realizados durante o desenvolvimento. O foco foi garantir a estabilidade da física da bola, a gestão de memória (criação/destruição de objetos) e a lógica de pontuação e power-ups.

## 2. Metodologia de Teste

* **Testes de Lógica:** Verificação de funções específicas (ex: `move()`, `checkCollisions()`, `atingir()`).
* **Testes de Integração:** Verificação da comunicação entre a Cena (`DuGraphicsScene`) e a Interface (`MainWindow`).
* **Testes de Regressão:** Garantia de que novas implementações (ex: PowerUps) não quebraram funcionalidades antigas.

## 3. Casos de Teste e Resultados

### 3.1. Física e Colisões
| ID | Descrição do Teste | Resultado Esperado | Resultado Obtido |
|:---:|:---|:---|:---|
| **01** | Colisão Bola vs. Parede | Bola deve inverter direção ao tocar nas bordas (exceto inferior). | Bola rebate corretamente e corrige posição para não "grudar".
| **02** | Colisão Bola vs. Tijolo (Topo/Baixo) | Bola deve inverter eixo Y (`vy`). | Detectado via `intersection.width > height`. Rebate verticalmente.
| **03** | Colisão Bola vs. Tijolo (Lateral) | Bola deve inverter eixo X (`vx`). | Detectado via `intersection.height > width`. Rebate lateralmente.
| **04** | Aceleração da Bola | Velocidade deve aumentar ao bater na raquete ou quebrar tijolo. | Incremento linear respeitando `MAX_SPEED`.

### 3.2. Mecânicas de Jogo
| ID | Descrição do Teste | Resultado Esperado | Resultado Obtido |
|:---:|:---|:---|:---|
| **05** | Durabilidade dos Tijolos | Tijolos devem mudar de cor ao receber dano (Verde -> Amarelo -> Vermelho). | Tijolos decrementam `mHits` e atualizam `QBrush` corretamente.
| **06** | Spawn de Power-Up | Chance percentual de dropar item ao quebrar tijolo. | Drop ocorre em ~30% das quebras na posição exata do bloco destruído.
| **07** | Efeito Power-Up: Multiball | Criar 2 bolas extras amarelas ao coletar. | Criação correta (sem loop duplicado) e bolas herdam física independente.
| **08** | Efeito Power-Up: Expand | Aumentar largura da raquete. | Raquete expande. Lógica implementada para impedir spawn se já estiver expandida.
| **09** | Game Over | Perder todas as bolas encerra o jogo. | Detecção de `mBallList.isEmpty()` funciona e para o Timer.
| **10** | Vitória | Destruir todos os tijolos encerra o jogo. | Detecção de `mBlockList.isEmpty()` dispara tela de vitória.

### 3.3. Interface e Sinais
| ID | Descrição do Teste | Resultado Esperado | Resultado Obtido |
|:---:|:---|:---|:---|
| **11** | Atualização de Score | HUD deve mostrar soma total de pontos de todas as bolas. | Implementado padrão "Coletar e Zerar" pontos da bola para o `mTotalScore`. Sincronia perfeita.
| **12** | Barra de Velocidade | Mostrar a velocidade atual na barra de progresso. | Barra reflete a maior velocidade entre todas as bolas ativas (`maxSpeedFound`).
| **13** | Tela de Vitória | Exibir "YOU WIN" e Score Final sobre o jogo. | Overlay (`QLabel` e `QLCDNumber`) aparece via `raise()` e `show()`.
| **14** | Reset via Teclado | Tecla ESPAÇO deve reiniciar apenas se perdeu/ganhou. | Reset funcional, limpando listas de memória e reposicionando objetos.
| **15** | Estado dos Botões | Botões Play/Reset devem habilitar/desabilitar conforme estado. | Sinais `gameReset`, `gameOver` e `gameWin` controlam botões corretamente.

## 4. Registro de Bugs Encontrados e Corrigidos
Durante o processo de desenvolvimento, os seguintes desafios críticos foram identificados e solucionados:

1. **Bug da Aceleração Nula:**
   * *Problema:* A bola não acelerava nas laterais.
   * *Causa:* Erro de sintaxe C++ `mvx = mvx++` (comportamento indefinido).
   * *Solução:* Código corrigido para `if(mvx > 0) mvx++;`.

2. **Bug das Bolas Pretas:**
   * *Problema:* Novas bolas do PowerUp nasciam pretas.
   * *Causa:* Falta de atribuição da variável `mColor` no construtor do `DuBallItem`.
   * *Solução:* Adicionada linha `mColor = color;` no construtor.

3. **Bug de Colisão "Fantasma":**
   * *Problema:* A bola atravessava tijolos ou rebatia errado nas quinas.
   * *Causa:* Uso de colisão simples (`intersects`).
   * *Solução:* Implementação de lógica de interseção geométrica (`intersected().width vs height`) para determinar lado da batida.

4. **Bug de Sincronia de Score na Vitória:**
   * *Problema:* A tela de vitória mostrava pontuação atrasada (faltando o último bloco).
   * *Causa:* `MainWindow` lia o display antes do update final.
   * *Solução:* Alterado sinal `gameWin()` para `gameWin(int score)`, passando o valor atualizado diretamente.

## 5. Conclusão

A implementação atual é estável, livre de vazamentos de memória conhecidos e atende aos requisitos de um jogo estilo Arkanoid funcional com sistema de progressão, power-ups e mecânicas adequadas.
