----------------------------------------------------------------------------------------------------------------------------------------------
Docker Volumes:
----------------------------------------------------------------------------------------------------------------------------------------------

→ Container data is temporary
→ Container stops / crashes / removed → data is lost
→ Persistent storage managed by Docker
→ MySQL container recreated → data still exists

→ Multiple containers can use the same volume
→ Used for shared logs + uploads + data

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Volume Implementation:

'docker volume create mysql-data'
    → creates a Docker-managed volume

'docker run --name mysql-db -v mysql-data : /var/lib/mysql mysql:8.0'
    → MySQL stores data in /var/lib/mysql

'docker volume inspect mysql-data'
    → display volume meta-data

'docker volume ls'
    → show all volumes

----------------------------------------------------------------------------------------------------------------------------------------------

Regular Folder Bind (Bind Mounts): 
    → Connect Host folder to container folder
    → Container writes → saved in host folder
    → Not managed by Docker
    → Used for dev + testing

Implementation:

1: Create folder on host machine
2: Bind folder to the container
3: 'docker run --name mysql -v <host-folder> : <var/lib/mysql> Mysql.0'

----------------------------------------------------------------------------------------------------------------------------------------------