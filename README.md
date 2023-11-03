Trabalho Prático I - Engenharia de Software II

1.1 - Integrantes Victor Della Croce Maltez - 2019042392

1.2 - Sistema 

O sistema é de alocação de bicicletas em uma região especifica, o qual recebe um mapa com a posição dos visitantes e das bicicletas e uma lista indicando o grau de preferência de cada visitante com cada bicicleta disponível.

A alocação segue uma condição de estabilidade de 'casamento estável', seguindo os seguintes critérios: - Se há uma bicicleta b2 que p1 considere preferível em relação à b1, então há uma pessoa p2 mais próxima de b2 que ela considera preferível a b1. - Se há uma pessoa p2 que está mais próxima de b1 do que p1, então p2 foi alocada para alguma bicicleta b2 que ela considera preferível a b1.

O sistema segue uma ordem de chegada, a qual é representada pelo ID, ou seja, quanto menor o ID, maior a prioridade do visitante, nos casos em que 2 ou mais visitantes desejam a mesma bicicleta ou estejam a mesma distância.

1.3 - Tecnologias 

O sistema foi desenvolvido na linguagem C++ e sua modelagem foi baseada na transformação do mapa passado como parâmetro em uma matriz MxN, simulando um grafo, sendo que cada célula Cij (0 ≤ i ≤ M e 0 ≤ j ≤ N) representa um nó, o qual está conectado à todas suas células adjacentes exceto as que representam obstáculos do mapa. Dessa forma, os nós que representam as células as quais simbolizam obstáculos, não estão conectadas a nenhum outro nó.

Para solução do problema, foi utilizado o método de 'Breadth First Search' na matriz que simula o grafo, para encontrar a menor distância entre os visitantes e as bicicletas. Outro método utilizado foi o de 'Gale-Shapley', de forma que sempre encontre a melhor combinação entre visitantes e bicicletas, de forma que todos fiquem satisfeitos.