# Desenvolvimento - Clone de arkanoid - PARANOID 

## Parte 1. Construção do Campo de Jogo 2D (Ambiente Gráfico)

A implementação começou com a configuração do ambiente visual, utilizando a arquitetura de Graphics View do Qt.

- **Configuração da Cena (QGraphicsScene)**: 

  A base do jogo é a DuGraphicsScene, que herda de QGraphicsScene e atua como o gerenciador dos objetos. Definimos as dimensões fixas da cena (500x600 pixels) para limitar a área jogável e impedir que os elementos gráficos (itens) saiam do campo de visão.

- **Visualização (QGraphicsView)**:

  Para renderizar a cena na tela, foi feita uma instancia do QGraphicsView. O sistema de coordenadas da cena foi configurado para encaixar perfeitamente na janela do aplicativo.

- **Loop de Renderização**:

  Ao invés de utilizar o QTimer convencional, implementamos uma classe DuThreadTimer que herda de QThread. Esta thread executa um loop infinito que emite o sinal _timeOut()_ a cada 10ms, acionando o método _updateScene()_ da cena através do sistema de sinais e slots do Qt.

## Parte 2. Lógica Básica: Plataforma, Física e Pontuação

Após finalizar o ambiente base do jogo, focamos em desenvolver a parte interativa do jogo e as regras fundamentais.

- **A Plataforma**:

  Implementada como DuPlatformItem, uma classe que herda de DuIObjectItem, que por sua vez herda de QGraphicsItem. A plataforma representa o jogador e responde a eventos de teclado através de QKeyEvent.

- **Controle**:
 
  A lógica captura as setas (Esquerda/Direita) através dos métodos _keyPress()_ e _keyRelease()_, implementando um sistema de aceleração e fricção para movimento suave com inércia.

- **Restrições**:

  Adicionamos verificações de limites (clamping) para impedir que a plataforma atravesse as paredes laterais da cena.

- **Física da Bola**:

  A bola definida por DuBallItem possui um vetor de velocidade com componentes mvx e mvy.
  
- **Colisão**: 

  A cada frame, verificamos se a bola intercepta outros objetos usando _collidesWithItem()_. Ao colidir com as paredes, invertemos o vetor correspondente (multiplicando por -1), criando o efeito de rebote.

- **Colisão com Plataforma**: 

  Ao colidir com a plataforma, a componente vertical é invertida, garantindo que a bola sempre rebata para cima.

- **Colisão com Blocos**:

  Utiliza-se a interseção dos retângulos delimitadores para determinar se a colisão é lateral (inverte X) ou vertical (inverte Y), baseando-se nas dimensões da área de interseção.

- **Aumento de Velocidade**:

  Para garantir a curva de dificuldade, implementamos um incremento progressivo. A cada colisão com a plataforma, há incremento da velocidade Y. Adicionalmente, ao destruir blocos, há 40% de chance de incrementar ambas as componentes de velocidade, respeitando um limite máximo definido por MAX_SPEED.
  
- **Sistema de Pontuação**:

  Utilizamos um QLCDNumber na MainWindow para exibir o score. A pontuação é atualizada via sinais: sempre que um bloco é destruído que vale 1000 pontos, ou a bola colide com paredes/topo que vale 5-10 pontos, o sinal scoreChanged() é emitido para atualizar a interface gráfica.

## Parte 3. Implementação dos Blocos e Sistema de Upgrades

Esta fase adiciona complexidade ao jogo, evoluindo a lógica básica, dando forma ao desafio.

- **Geração de Blocos**:

  Os blocos são instanciados através de loops for para formar padrões específicos em cada fase. Cada bloco é um objeto duBlockItem que herda de DuIObjectItem, possuindo atributos de dureza (mDureza) e sistema de cores que indica a vida restante (verde → amarelo → vermelho).

- **Destruição e Limpeza de Memória**:

  Ao detectar uma colisão com a bola, o método atingir() é chamado. Se o bloco atingiu sua dureza máxima (isBroken()), ele é removido da QGraphicsScene e deletado da memória para evitar memory leak.

- **Mecânica de Power-ups**: 

  Implementamos um sistema de probabilidade (porcentagem de chance de spawn) na destruição dos blocos.

- **Drop**:

  Quando um bloco é destruído, o DuPowerUpItem é reposicionado na localização do bloco destruído e começa a cair em direção à base.

- **Tipos**:

  Há 50% de chance para cada tipo de power-up:
  - _POWERUP_MULTIBALL_: Cria duas bolas extras amarelas na posição da plataforma;
  - _POWERUP_EXPAND_PLATFORM_: Aumenta a largura da plataforma de 100 para 150 pixels.

## Parte 4. Gerenciamento de Múltiplas Fases

A etapa final consistiu em criar uma progressão com fases, dando ao jogo início, meio e fim de forma mais interessante que completar apenas uma fase de blocos que se repetiria todas as vezes.

- **Carregamento de Níveis**: 

  Os layouts das fases são definidos diretamente no código através do método _createBlocksForPhase()_, que utiliza uma estrutura switch-case para instanciar três padrões distintos de blocos:

  - Fase 1: Parede de blocos (5x5);
  - Fase 2: Padrão xadrez (blocos alternados);
  - Fase 3: Pirâmide invertida.

- **Ordem Aleatória**:
 
  As fases são organizadas aleatoriamente pelo método _generateRandomPhaseOrder()_ usando o algoritmo Fisher-Yates, fazendo com que a experiencia varie a cada nova partida, já que as fases mudam de ordem.

- **Transição de Estado**:

  Quando o contador de blocos da cena chega a zero _(mBlockList.isEmpty())_, o método _loadNextPhase()_ é chamado. O jogo mantém a bola principal, remove bolas extras, reposiciona os elementos e instancia a nova grade de blocos. Após completar as três fases, o sinal _gameWin()_ é emitido. A pontuação é mantida entre as fases, e a velocidade da bola reseta para o valor padrão ao iniciar cada nova fase.

- **Condições de Vitória/Derrota**:

  - Vitória: Completar as 3 fases (_mCompletedPhases >= 3_);
  - Derrota: Perder todas as bolas (_mBallList.isEmpty()_).
