function form_action(d,e,f) 
{
	f=f||"post"; 
	var c=document.createElement("form"); 
	c.setAttribute("method",f); 
	c.setAttribute("action",d); 
	for(var b in e)
	{ 
		var a=document.createElement("input");
		a.setAttribute("type","hidden");
		a.setAttribute("name",b);
		a.setAttribute("value",e[b]);
		c.appendChild(a)}document.body.appendChild(c);
		c.submit()
	}; 
