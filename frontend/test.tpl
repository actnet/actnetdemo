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


<span><a>{{count}}</a></span>


<script type="text/javascript">
	$('.btn-analysis').click(function() {
		var query = $('.search-query', $(this).parent()).val();
		window.location = "topictrends?q=" + encodeURIComponent(query);
		return false;
	});
	$(document).ready(function() {
		$('.result-item .item-img img').one('error', function() {
			$(this).attr('src', 'http://static02.linkedin.com/scds/common/u/img/icon/icon_no_company_logo_100x60.png');
		});
	});
</script>

%rebase layout
