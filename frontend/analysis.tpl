<style type="text/css">
	.result-item {
		padding: 4px 2px 4px 6px;
		border-bottom: 1px dashed #f6f6f6;
	}

	.item-img {
		max-width: 120px;
		padding: 2px;
		border: 1px solid #ddd;
		border-radius: 4px;
	}

	.item-img:hover {
		border-color: #0088cc;
	}

	.item-stats {
		color: green;
		font-size: 12px;
	}

	ul.item-stats > li {
		margin-left: 0;
		padding-left: 0;
	}

	.item-description {
		color: grey;
		margin: 0;
	}

	.item-topics > li {
		padding-left: 0;
		font-size: 11px;
		border: solid 1px rgba(99, 99, 99, 0.18);
	}

	.extra-results {
		line-height: 14px;
	}

	.extra-item {
		padding: 4px 2px 4px 6px;
		border-bottom: 1px dashed #f6f6f6;
	}

	.extra-item-title {
		color: black;
		font-size: 12px;
	}

	.extra-item-authors {
		color: green;
		font-size: 12px;
	}

	.extra-item-stats {
		line-height: 14px;
		height: 12px;
		color: grey;
	}

	.extra-item-stat {
		margin-left: 6px;
	}

</style>

<form action = "/analysis/upload" method = "POST" enctype="multipart/form-data">
	<fieldset>
		<legend>Cloud Analysis</legend>
		<input type="file" name="data"/>
		<button class="btn btn-primary" type="submit">Upload</button>
	</fieldset>
</form>
{{warning}}
<br><br><br>

Current Files
%for file in files:
<li>{{file}} : <a href="/download_in/{{file}}">download</a> <a href="/remove_in/{{file}}">remove</a> <a href="/launch/{{file}}">launch</a></li>
%end

<br><br><br>
Parameter Control Panel<br>
Xmin: <input type="text" name="xmin" value="1"> Xmax: <input type="text" name="xmax" value="10"><br>
Ymin: <input type="text" name="ymin" value="0"> Ymax: <input type="text" name="ymax" value="1.0"><br>

<br><br><br>

Distribution Graph<br>
%for file in results:
<li>{{file}} : <a href="/download_out/{{file}}">download</a> <a href="/remove_out/{{file}}">remove</a></li>
%end



%rebase layout
