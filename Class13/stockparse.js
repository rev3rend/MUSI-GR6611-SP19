// hi there
var cookeddata;
var thegoodstuff=[];

function stuff(s)
{
	thegoodstuff = []; // initialize the final array
	// parse the JSON coming in into an object literal:
	cookeddata = JSON.parse(s); 
	for(var i in cookeddata["Time Series (5min)"])
	{
		var s = cookeddata["Time Series (5min)"][i];
		for(var j in s)
		{
			if(j=="4. close")
			{
				post(s[j] + '\n');
				var foo = parseFloat(s[j]); // interpret as number
				thegoodstuff.push(foo);
			}
		}
		//post(i + '\n');
	}
	//post(s + '\n'); // to the MAX window
	outlet(0, thegoodstuff);
}