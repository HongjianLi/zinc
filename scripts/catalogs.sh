n=0
curl http://zinc.docking.org/browse/catalogs/ | tail -n +247 | head -2277 | while read -r line; do
	if [[ $n = 1 ]]; then
		abbr=${line:37:$(expr index "${line:37}" "\"")-1}
		echo -n $abbr,
	fi
	if [[ $n = 6 ]]; then
		echo -n ${line:0:${#line}-15},
		curl zinc.docking.org/catalogs/$abbr | while read -r link; do
			if [[ ${link:0:5} = "<dd><" ]]; then
				addr=${link:13:$(expr index "${link:13}" "\"")-1}
				if [[ $addr != "http://web" && $addr != "http://website" && $addr != "http://no web" ]]; then
					echo -n $addr | tr -d ' '
				fi
				echo
				break
			fi
		done
	fi
	n=$((n+1))
	if [[ $n = 9 ]]; then
		n=0
	fi
done
