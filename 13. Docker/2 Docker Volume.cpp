----------------------------------------------------------------------------------------------------------------------------------------------
Docker Volumes:
----------------------------------------------------------------------------------------------------------------------------------------------

→ Container data is temporary
→ If Container stops/crashes/removed → data lost
→ Persistent storage
→ Use for: DB data, shared logs, file uploads

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Volume Implementation:

'docker volume create mysql-data'             → create a named volume
'docker volume ls'                            → list all volumes
'docker volume inspect mysql-data'            → show volume metadata + location

'docker run --name mysql-db -v mysql-data:/var/lib/mysql mysql:8.0':
    → mount volume to container path
    → MySQL writes to /var/lib/mysql → actually stored in volume → persists

----------------------------------------------------------------------------------------------------------------------------------------------

Regular Folder Bind (Bind Mounts): 
    → You directly link a folder on your host machine to a folder inside container
    → Container writes → files appear on your host machine
    → NOT managed by Docker → you control the location
    → Use for: local dev, testing, seeing logs on your machine

'docker run --name mysql -v /your/host/folder:/var/lib/mysql mysql:8.0'

----------------------------------------------------------------------------------------------------------------------------------------------\

Volumes vs Bind Mounts:
    Docker Volume  → Docker manages location → production, DB data
    Bind Mount     → You choose location → local dev, quick testing

----------------------------------------------------------------------------------------------------------------------------------------------\
