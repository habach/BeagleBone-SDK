ko=${1%.*}.ko
echo -n "Copying $ko to $2 ..."
scp $ko "$2"
echo -n "Done.\n"
