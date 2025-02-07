var sbar_toggler = {
sidebar_open: true,
toggle: function() { 
     //var side_bar = document.getElementById("left_sidebar").style;
	 //var right_page = document.getElementById("right_page").style;
	 var side_bar = this.get_div_style("left_sidebar");	 
	 var right_page = this.get_div_style("right_page");
	 var bar_bottom = document.getElementById('bar__bottom').style;
	
	 if(!side_bar || !right_page) return;
     if(this.sidebar_open) {
	    side_bar.display = 'none';
		right_page.width = "95%";
		bar_bottom.width = "92%";
		this.sidebar_open = false;
		return;
	 }
	    side_bar.display = 'block';
		right_page.width = "80%";
		bar_bottom.width = "77%";
        this.sidebar_open = true;
},

get_div_style: function(className) {
      var hasClassName = new RegExp("(?:^|\\s)" + className + "(?:$|\\s)");
      var divs = document.getElementsByTagName('div');
	  var element;
		for (var i = 0; (element = divs[i]) != null; i++) {
			var elementClass = element.className;
			if (elementClass && elementClass.indexOf(className) != -1 && hasClassName.test(elementClass))
				return element.style;
		}

		return null;	  
} 

};
/*
if (document.getElementsByClassName == undefined) {
	document.getElementsByClassName = function(className)
	{
		var hasClassName = new RegExp("(?:^|\\s)" + className + "(?:$|\\s)");
		var allElements = document.getElementsByTagName("*");
		var results = [];

		var element;
		for (var i = 0; (element = allElements[i]) != null; i++) {
			var elementClass = element.className;
			if (elementClass && elementClass.indexOf(className) != -1 && hasClassName.test(elementClass))
				results.push(element);
		}

		return results;
	}
}
*/