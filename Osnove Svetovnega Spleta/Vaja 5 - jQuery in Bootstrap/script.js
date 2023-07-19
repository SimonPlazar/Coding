console.log("js");

	$(document).ready(function(){
		nalozi()
		
		$('ul').on('click', 'li', function() {
			/*V tej funkciji dodamo class active kliknjenem elementu li, ki smo ga kliknili in odstranimo staremu.*/
			
			if($(this).hasClass("active")){
				$(this).toggleClass("active");
			}else{
				$(".active").toggleClass("active");	
				$(this).toggleClass("active");
			}
			shrani();
		});
		
		$("#dodaj").click(function(){
			/*V tej funkciji dodamo novo vrstico v seznmu*/
			var vnos = $("#vnos").val();
			if(vnos==""){
				vnos="Blank"
			}
			var novi = document.createElement("li");
			novi.innerHTML = vnos;
			$("ul").append(novi);
			$("li").addClass("list-group-item");
			shrani();
		});
		
		$('#confirm-delete').on('click', '.btn-ok', function() {
			/*V tej funkciji zbrišemo izbrano vrstico v seznmu*/
			$(".active").remove();
			$('#confirm-delete').modal('hide')
			shrani();
		});
		
		$('tbody').on('click', 'tr', function() {
			/*V tej funkciji dodamo Class selected in Kliknjen elementu li, ki smo ga kliknili in odstranimo staremu.*/
			console.log("Clicked", this);
			$(this).toggleClass("tselected");
			shrani();
		});
		
		$("#tdodaj").click(function(){
			/*V tej funkciji dodamo novo vrstico v tabelo*/
			var tabela = $('table > tbody');
			var tvnos = $("#tvnos").val();
			var kategorija = $(".active").html();
			
			console.log(vnos);

			if(tvnos==""){
				tvnos="Blank"
			}
			
			if(kategorija==undefined){
				kategorija="Blank"
			}
			
			count++;
			
			var row = document.createElement("tr");
			var td1 = document.createElement("td");
			var td2 = document.createElement("td");
			var td3 = document.createElement("td");
			var td4 = document.createElement("td");

			td1.innerHTML = count;
			td2.innerHTML = tvnos;
			td3.innerHTML = kategorija;
			td4.innerHTML = new Date();
			
			row.append(td1);
			row.append(td2);
			row.append(td3);
			row.append(td4);
			
			tabela.append(row);	
			shrani();
		});
		
		$('#confirm-delete2').on('click', '.btn-ok', function() {
			/*V tej funkciji zbrišemo izbrane vrstice v tabeli*/
			$(".tselected").remove();
			$('#confirm-delete2').modal('hide')
			shrani();
		});
		
		$("#lbrisi").click(function(){
			localStorage.clear();
		});
		
	});
	var count = 0;
	
	
	function shrani(){
		/*V tej funkciji shranemo count, seznam in tabelo v localStorage*/
		localStorage.setItem("seznam",$("ul").html());
		localStorage.setItem("tabela",$("tbody").html());
		localStorage.setItem("count",count);
	}
	
	function nalozi(){
		/*V tej funkciji nalozimo seznam in tabelo iz localStorage-a*/
		if(localStorage.count>0){
			count=localStorage.count;
		}
		if(localStorage.seznam){
			$("ul").html(localStorage.seznam);
		}
		if(localStorage.seznam){
			$("tbody").html(localStorage.tabela);
		}
	}
	