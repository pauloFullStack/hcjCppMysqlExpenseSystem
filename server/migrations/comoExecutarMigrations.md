##### Como executar os codigos sql:

###### Para executar o comando mysql -u seu_usuario -p < seuarquivo.sql, o arquivo SQL (seuarquivo.sql) deve estar localizado no diretório atual do seu terminal ou prompt de comando. O diretório atual é o diretório em que você se encontra quando executa o comando.
###### OBS: na hora de colocar a senha '-psua_senha', pode deixar em branco para o proprio sistema perdir, isso é boa pratica
```
mysql -useu_usuario -psua_senha < seuarquivo.sql
mysql -uuser_paulo -pDavi91445129! < createTableLogin.sql
```

###### Ou executar em lote:
```
mysql -useu_usuario -psenha < arquivo1.sql arquivo2.sql arquivo3.sql
```