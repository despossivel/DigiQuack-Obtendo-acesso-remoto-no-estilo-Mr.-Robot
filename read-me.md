PASSOS 

1 - Criar uma INSTANCIA e definir um IP estatico

    Eu estarei utilizando o GCP(Google cloud platform) mas você pode utilizar o provedor de CLOUD que deseja ou até mesmo um VPS.

    1 - Acesso meu console e crio a instancia. Estancia essa que é bem basica uma micro com SO Debian 9

    2 - Com o a instancia criada, eu defino um IP estatico para minha instancia. Um IP estatico é necessario para que não ocorra o risco do IP mudar e perdemos nossos "computadores zumbis" já conquistados.

2 - Instalar METASPLOIT e NGINX


        Nesse passo vamos instalar nosso canivete suiço METASPLOIT para criamos nosso BACKDOOR e orquestramos nossos "computadores zumbis" o nginx vai ser necessario para que o nosso payload do Digispark possa fazer o download do BACKDOOR para dentro da maquina alvo.

        1 - Conecte a sua instancia por ssh para instalarmos o METASPLOIT e o NGINX para isso rode 

            $ ssh usuario@instancia 

            apos se conectar rode instale o nginx ou apache como preferir

            $ sudo apt-get install -y nginx

            agora os comandos abaixo é para instalar o METASPLOIT

            $ curl https://raw.githubusercontent.com/rapid7/metasploit-omnibus/master/config/templates/metasploit-framework-wrappers/msfupdate.erb > msfinstall

            conceder permisão de execução para o instalador

            $ chmod +x msfinstall

            agora execulte o mesmo

            $ ./msfinstall

            Efeito isso e não deu nenhum error é so verificar se ta tudo certo

            $ msfconsole --version

3 - Criar BACKDOOR REVERSE





4 - Configurar NGINX para download do backdoor

5 - Digispark

6 - Criar Payload injectar o backdoor

7 - INICIAR ESCULTA DAS CONEXOES DO BACKDOOR

8 - Obter acesso a uma maquina infectada