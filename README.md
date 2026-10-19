# Repositório para o Desafio de Prog II

## Alterações Feitas até agora.

- Modularização
  - Cadastros movidos para arquivo próprio
  - Structs movidas para arquivo próprio
  - Ordenações movidas para um unico arquivo

- Validação
  - Cada cadastro agora valida as entradas do usuário
  - Criação de um objeto temporário durante a validação para evitar a criação de registros parciais

- Ordenações
  - As ordenações agora alteram um struct de Ordem, para facilitar a busca nos registros originais, que se mantem sempre por ID

- Buscas e Ordenações implementadas na lógica principal

- O Que falta:
  - Implementar funcionalidades recursivas
  - Relatorio de desempenho
  - Relatório escrito