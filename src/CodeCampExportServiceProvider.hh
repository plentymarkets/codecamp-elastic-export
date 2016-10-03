<?hh // strict
namespace CodeCampExport;

use Plenty\Modules\DataExchange\Services\ExportPresetContainer;
use Plenty\Plugin\DataExchangeServiceProvider;

use CodeCampExport\Generators\AwesomeMarketplaceGenerator;
use CodeCampExport\ResultFields\AwesomeMarketplaceResultFields;
use CodeCampExport\Filters\AwesomeMarketplaceFilters;

class CodeCampExportServiceProvider extends DataExchangeServiceProvider
{
	public function register():void
	{
	}

	public function exports(ExportPresetContainer $container):void
	{
		$container->add(
				'AwesomeMarketplace',
				AwesomeMarketplaceResultFields::class,
				AwesomeMarketplaceGenerator::class,
				AwesomeMarketplaceFilters::class
			);
	}
}
