function setA()
{
   A = parseFloat(document.form1.A.value)/1000.0;
   //document.form2.Failed.value = A*1000
   draw();
   Model_Calculator();
}

function setB()
{
   B = parseFloat(document.form1.B.value)/10000.0;
   //document.form2.Failed.value = B*10000;
   draw();
   Model_Calculator();
}

function setC()
{
    C = parseFloat(document.form1.C.value)/10000000.0
    //document.form2.Failed.value = C*10000000;
    draw();
    Model_Calculator();
}

function setR25()
{
    R25 = parseFloat(document.form1.R25.value);
    if (R25<0) R25=0;
    document.form1.R25.value = R25;
    //document.form2.Failed.value = R25;
    draw();
    Model_Calculator();
   
}

function setBeta()
{
    Beta = parseFloat(document.form1.Beta.value);
    //document.form2.Failed.value = Beta;
    draw();
    Model_Calculator();
    
}

function increaseR()
{
    Rth++;
    document.form2.Rth.value = Rth;
    Model_Calculator();
}

function decreaseR()
{
    Rth--;
    document.form2.Rth.value = Rth;
    Model_Calculator();
}

function Model_Calculator()
{
	Rth = parseFloat(document.form2.Rth.value);
	if (Rth<1){Rth=1; document.form2.Rth.value=Rth;}
	var Tsteinhart = 1/(A+B*Math.log(Rth)+C*Math.pow(Math.log(Rth),3))-273.15;
	var Tbeta = 1/(1/(273.15+25)+1/Beta*Math.log(Rth/R25))-273.15;
	document.form2.Tsteinhart.value = Tsteinhart.toFixed(4);
	document.form2.Tbeta.value = Tbeta.toFixed(4);
	
}

function TbetaToRth()
{
    var Tbeta = parseFloat(document.form2.Tbeta.value);
        Rth = R25 * Math.exp(- Beta * (Tbeta - 25)/ (Tbeta + 273.15)/ 298.15);
    document.form2.Rth.value = Rth.toFixed(2);
    Model_Calculator();
}

function TsteinhartToRth()
{
    var Tsteinhart = parseFloat(document.form2.Tsteinhart.value);
    var X = (A-1/(Tsteinhart+273.15))/C;
    var Y = Math.sqrt((B*B*B/C/C/C/27)+(X*X)/4);
        Rth = Math.exp(Math.pow((Y-X/2),(1/3))-Math.pow((Y+X/2),(1/3)));
    document.form2.Rth.value = Rth.toFixed(2);
    Model_Calculator();
}

function Cal()
{
    // Add validation code here
   
     R1 = parseFloat(document.form1.R1.value);    
     T1 = parseFloat(document.form1.T1.value); 
     R2 = parseFloat(document.form1.R2.value);
     T2 = parseFloat(document.form1.T2.value);
     R3 = parseFloat(document.form1.R3.value);
     T3 = parseFloat(document.form1.T3.value);
    
     
     var T0 = 273.15 + 25;
      T1 = 273.15 + T1;
      T2 = 273.15 + T2;
      T3 = 273.15 + T3;
     if (R1>5 && R2>5 && R3>5 && R1!=R2 && R2!=R3 && R1!=R3 && T1!=T2)
     {
	Fail = 0;
	Beta = - T1 * T2 * Math.log(R1/R2) / (T1-T2);
	R25 = R1 / (Math.exp(- Beta * (T1 - T0)/ T1 / T0));
	C =((1/T1-1/T2)-(Math.log(R1)- Math.log(R2))*(1/T1-1/T3)/(Math.log(R1)-Math.log(R3)))/((Math.pow(Math.log(R1),3)-Math.pow(Math.log(R2),3)) - (Math.log(R1)-Math.log(R2))*(Math.pow(Math.log(R1),3)-Math.pow(Math.log(R3),3))/(Math.log(R1)-Math.log(R3)));
        B =((1/T1-1/T2)-C*(Math.pow(Math.log(R1),3)-Math.pow(Math.log(R2),3)))/(Math.log(R1)-Math.log(R2));
	A = 1/T1-C*(Math.log(R1))*(Math.log(R1))*(Math.log(R1))-B*Math.log(R1);
	Rmin = Math.min(R1, R2, R3);
	Rmax =Math.max(R1, R2, R3);
 
    } else {
	    Fail = 1;
	    Beta =0;
	    R25 = 0;
	    C = 0;
	    B = 0;
	    A = 0;
	    }
	
	document.form1.Beta.value = Beta.toFixed(2);
	document.form1.R25.value = R25.toFixed(2);
	    var AA = A*1e+3;
	    var BB = B*1e+4;
	    var CC = C*1e+7;
	document.form1.A.value = AA.toPrecision(10);
	document.form1.B.value = BB.toPrecision(10);
	document.form1.C.value = CC.toPrecision(10);
	

    Model_Calculator();// call thermistot calculator	
    draw();
}  
    
function draw()
{
    if (Fail<1)
	{
	    	
        var SHH = [], BM = [];
        var Rt = Rmin * 0.5;
	var Rtm = Rmax * 1.5;
		
            while (Rt < Rtm)
            {
	    Rt = Rt*(1+(Rmax-Rmin)/Rmax*0.4);
	    //Rt+=(Rmax-Rmin)/5;
	    //document.write(Rt +'_');	    
	    SHH.push([1/(A+B*Math.log(Rt)+C*(Math.log(Rt))*(Math.log(Rt))*(Math.log(Rt)))-273.15, Rt]);    //1/(A+B*Math.log(Rt)+C*(Math.log(Rt))*(Math.log(Rt))*(Math.log(Rt)))-273.15
            BM.push([1/(1/(273.15+25)+1/Beta*Math.log(Rt/R25))-273.15, Rt]);         //1/(1/(273.15+25)+1/Beta*Math.log(Rt/R25))-273.15
            }

             
         datasets =
            {
	    "Beta": {
                label: "&beta; model",
                data: BM,
		points: { show: true },
		lines: { show: true }

                },
		
	    "Steinhart": {
                label: "S-H model",
                data: SHH,
		points: { show: true },
		lines: { show: true }

                },        
 		
	    "Orignal": {
                label: "Data",
                data: [[T1-273.15, R1], [T2-273.15,R2],[T3-273.15,R3]],
		points: { show: true },
		lines: { show: false }
		}
            };
           

	}else{
	    datasets =
            {
	    "Beta": {
                label: "&beta; model",
                data: [25, 10000],
		points: { show: true },
		lines: { show: true }

                },
		
	    "Steinhart": {
                label: "S-H model",
                data: [25, 10000],
		points: { show: true },
		lines: { show: true }

                },        
 		
	    "Orignal": {
                label: "Data",
                data: [25, 10000],
		points: { show: true },
		lines: { show: false }
		}
            };
 	}
	
	var i = 0;
	    $.each(datasets, function(key, val)
	    {
	       val.color = i;
	       ++i;
	    });
	    
	choiceContainer.find("input").click(plotAccordingToChoices);  
	plotAccordingToChoices();

            function plotAccordingToChoices()
            {
                var data = [];
                choiceContainer.find("input:checked").each(function ()
                {
                    var key = $(this).attr("name");
                    if (key && datasets[key])
                        data.push(datasets[key]);
                });

                if (data.length > 0)
		    $.plot($("#placeholder"), data,
                    {
			grid: { hoverable: true, clickable: false },
                        axis: { min: Rmin * 0.5, max: Rtm*1.05 }
                    });
            }

                $("#placeholder").bind("plothover", function (event, pos, item)
                {
                    $("#x").text(pos.x.toFixed(1));
                    $("#y").text(pos.y.toFixed(0));
                });
}
	