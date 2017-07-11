apt-get install python-dev libboost-dev libboost-system-dev

python setup.py build_ext -f -I wrapper:skaarhoj/ATEMbase:skaarhoj/ATEMmax -l boost_system
python setup.py install --user
