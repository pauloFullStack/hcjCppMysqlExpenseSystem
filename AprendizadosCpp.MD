### Apredizado c++:

##### O que são soquetes: 

###### Um soquete (socket) é uma interface de programação de aplicativos (API) que permite a comunicação entre processos ou programas em diferentes computadores ou em uma mesma máquina. Os soquetes são amplamente usados em redes de computadores para estabelecer conexões e permitir a transferência de dados entre sistemas.

###### Aqui estão algumas características importantes dos soquetes:

###### Comunicação entre processos: Os soquetes permitem que processos ou programas em diferentes máquinas (ou no mesmo computador) se comuniquem e troquem informações.

###### Endereço IP e Porta: Cada soquete é identificado por um endereço IP e uma porta. O endereço IP identifica o computador ou dispositivo, enquanto a porta identifica um processo específico em um computador. Portas diferentes são usadas para diferentes tipos de comunicação.

###### Protocolo de Transporte: Os soquetes podem ser usados com diferentes protocolos de transporte, como TCP (Transmission Control Protocol) e UDP (User Datagram Protocol). O TCP é orientado à conexão e oferece garantias de entrega confiável, enquanto o UDP é mais leve e oferece uma comunicação não confiável.

###### Tipos de Soquetes: Existem diferentes tipos de soquetes, como soquetes de fluxo (stream sockets) e soquetes de datagrama (datagram sockets). Os soquetes de fluxo são usados com o protocolo TCP e oferecem uma conexão confiável, enquanto os soquetes de datagrama são usados com o protocolo UDP e oferecem comunicação não confiável e sem conexão.

###### API de Programação: Para usar soquetes em programas, as linguagens de programação fornecem uma API de soquete que permite a criação, configuração e uso de soquetes em aplicativos.

###### Os soquetes são amplamente utilizados em várias aplicações de rede, como servidores web (usando HTTP sobre TCP) = Quando dizemos "usando HTTP sobre TCP", estamos indicando que as solicitações e respostas HTTP são encapsuladas em pacotes TCP para serem transmitidas pela rede. Isso é importante porque o HTTP, por si só, não fornece garantias de entrega confiável, e é aí que o TCP entra em cena. O TCP cuida de todos os aspectos relacionados à confiabilidade da transmissão, garantindo que os dados do HTTP sejam entregues corretamente e em ordem.

###### Em resumo, quando você navega na web, seu navegador faz solicitações HTTP para servidores web. Essas solicitações e as respostas correspondentes são transmitidas usando o protocolo HTTP, mas esses dados são enviados através da infraestrutura do TCP para garantir a confiabilidade da comunicação. Portanto, a combinação de HTTP sobre TCP é fundamental para a funcionalidade da World Wide Web., servidores de email (usando SMTP, POP3, IMAP sobre TCP), transferência de arquivos (usando FTP sobre TCP), jogos online (usando UDP para baixa latência) e muito mais.

###### Em resumo, um soquete é uma abstração que permite a comunicação entre processos ou programas em diferentes computadores ou na mesma máquina, facilitando a troca de dados por meio de redes de computadores.

